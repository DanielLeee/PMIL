//////////////////////////////////////////////////////////////////////////
//Function: Implement Different Feature Descriptor 
//Author: Junyan Zhu, Technology Strategy 
//Date: created @ 20110623
//////////////////////////////////////////////////////////////////////////
#include "Feature.h"

#define FOR(i,n) for( int i=0; i<n; i++ )

//public interface

CFeature::CFeature(string configFileName)
{
	Clear(); 
	SetFtrNames(); 
	ReadParamters(configFileName); 
	m_numFtrs = ComputeFeatureLength();
}

void CFeature::Clear( void )
{
	m_isUsedVec.clear(); 
	m_ftrNameVec.clear(); 	
	m_SIFTLayer = 0; 
	m_numFtrs = 0;
	m_patchSize = 0; 
	m_HISTBins = 0; 
	m_HOGCellSize = 0;
	m_HOGNBins = 0; 
}

CFeature::~CFeature()
{
	Clear(); 
}

int CFeature::GetFeatureLength()
{
	return m_numFtrs; 
}


float* CFeature::GetFeatures(const Mat _oriImg)
{
	assert(!_oriImg.empty() && _oriImg.rows == _oriImg.cols);
	IplImage* src = &(IplImage)_oriImg;
	IplImage* dst = cvCreateImage(cvSize(m_patchSize, m_patchSize), IPL_DEPTH_8U, 3);	
	cvResize(src, dst);
	Mat oriImg(dst, true);
	cvReleaseImage(&dst);

	float* ftrs = new float[m_numFtrs]; 
	int offset = 0; 
	int width = oriImg.rows;
	Mat grayImg; 
	Mat LABImg; 
	Mat LUVImg; 
		
	cvtColor(oriImg, grayImg, CV_BGR2GRAY); 
	
	if (m_isUsedVec[FTRTYPE_COLOR])
	{
		cvtColor(oriImg, LUVImg, CV_BGR2Luv); 
	}

	if (m_isUsedVec[FTRTYPE_LAB])
	{
		cvtColor(oriImg, LABImg, CV_BGR2Lab); 
	}

	if (m_isUsedVec[FTRTYPE_COLOR])
	{
		ComputeColorDescriptor(LUVImg, ftrs, offset); 
	}

	if (m_isUsedVec[FTRTYPE_SIFT])
	{
		ComputeSIFTDescriptor(grayImg, ftrs, offset); 

		for (int i = 1; i < m_SIFTLayer; i++)
		{
			width /= 2; 
			Mat layerMat;  
			pyrDown(grayImg, layerMat, Size(width, width));
			ComputeSIFTDescriptor(grayImg, ftrs, offset); 
		}
	}

	if (m_isUsedVec[FTRTYPE_HIST])
	{
		ComputeGrayHistogram(grayImg, ftrs, offset); 
	}

	if (m_isUsedVec[FTRTYPE_HOG])
	{
		ComputeHOGDescriptor(grayImg, ftrs, offset); 
	}	

	if (m_isUsedVec[FTRTYPE_LAB])
	{
		ComputeLABHistogram(LABImg, ftrs, offset); 
	}	

	if (m_isUsedVec[FTRTYPE_GLCM])
	{
		ComputeGLCMFeatures(grayImg, ftrs, offset); 
	}

	if (m_isUsedVec[FTRTYPE_REGION])
	{
		ComputeREGIONFeatures(grayImg, ftrs, offset); 
	}

	return ftrs; 
}

//private member function 
int CFeature::ComputeFeatureLength()
{
	vector<int> vl;
	int length = 0;

	if (m_isUsedVec[FTRTYPE_COLOR])
	{
		vl.push_back(length);
		length += COLOR_FEATURE_LENGTH;		
	}

	if (m_isUsedVec[FTRTYPE_SIFT])
	{
		vl.push_back(length);
		length += SIFT_FEATURE_LENGTH * m_SIFTLayer; 
	}
	
	if (m_isUsedVec[FTRTYPE_HIST])
	{
		vl.push_back(length);
		length += m_HISTBins; 
	}

	if (m_isUsedVec[FTRTYPE_HOG])
	{
		vl.push_back(length);
		//length += m_HOGNBins * m_patchSize * m_patchSize / (m_HOGCellSize * m_HOGCellSize); 
		//length += m_HOGNBins * (1 + 4 + 16);
		length += m_HOGNBins * 3;
	}
		
	if (m_isUsedVec[FTRTYPE_LAB])
	{
		vl.push_back(length);
		length += m_LABLBins * m_LABaBins * m_LABbBins; 
	}

	if (m_isUsedVec[FTRTYPE_GLCM])
	{
		vl.push_back(length);
		length += 4 * 5;
		glcm.distance = m_GLCMDis;
		glcm.GrayLayerNum = m_GLCMGrayLevel;
	}

	if (m_isUsedVec[FTRTYPE_REGION]) {
		vl.push_back(length);
		length += 2;
	}

	vl.push_back(length);

	if (Parallel::rank == 0) {
		FILE* log = fopen(Expr::feature_file.c_str(), "w");

		fprintf(log, "Feature Total Length: %d\n", length);
		int idx = 0;
		FOR (i, NUM_FEATURE_TYPE)		
			if (m_isUsedVec[i])
			{
				fprintf(log, "%s : %d to %d\n", m_ftrNameVec[i].c_str(), vl[idx], vl[idx + 1] - 1);
				++idx;
			}		
		fprintf(log, "\n");

		fclose(log);
	}

	return length; 
}


void CFeature::ComputeSIFTDescriptor(const Mat grayImg, float* ftrs, int& offset)
{
	double angle0 = 0; 

	if (m_isAlignAngle)
	{
		angle0 = ComputeMainDirection(grayImg); 
	}

	const int NBO = 8;
	const int NBP = 4;
	const int binto = 1 ;
	const int binyo = NBO * NBP ;
	const int binxo = NBO;
	int width = grayImg.rows; 
	int height = grayImg.cols; 
	float x = width / 2 - 0.5f; 
	float y = width / 2 - 0.5f; 
	int xi = width / 2; 
	int yi = width / 2; 	
	FOR (i, SIFT_FEATURE_LENGTH)
	{
		ftrs[i+offset] = 0;
	}

	float st0 = (float)sinf(angle0); 
	float ct0 = (float)cosf(angle0); 

	for(int dyi = 1-yi; dyi <= width-2-yi ; ++dyi) 
	{
		for(int dxi = 1-xi ; dxi <= width-2-xi ; ++dxi)
		{
			float gx = grayImg.at<uchar>(dyi+yi, dxi+xi+1) - grayImg.at<uchar>(dyi+yi, dxi+xi-1); 
			float gy = grayImg.at<uchar>(dyi+yi+1, dxi+xi) - grayImg.at<uchar>(dyi+yi-1, dxi+xi);
			float mag = cv::sqrt(gx * gx +  gy * gy); 
			float theta = (float)fast_mod_2pi(-(atan2(gy, gx) + 2 * CV_PI) + angle0); 
			float dx = xi + dxi - x; 
			float dy = yi + dyi - y; 
			float nx = ( ct0 * dx + st0 * dy) * NBP / (float)width;
			float ny = (-st0 * dx + ct0 * dy) * NBP / (float)height;
			float nt = (float)NBO * theta / (2 * CV_PI); 
			int binx = (int)floor(nx-0.5); 
			int biny = (int)floor(ny-0.5); 
			int bint = (int)floor(nt); 
			float rbinx = nx - (binx+0.5f); 
			float rbiny = ny - (biny+0.5f); 
			float rbint = nt - bint; 

			for(int dbinx = 0 ; dbinx < 2 ; ++dbinx) 
			{
				for(int dbiny = 0 ; dbiny < 2 ; ++dbiny) 
				{
					for(int dbint = 0 ; dbint < 2 ; ++dbint) 
					{
						if( binx + dbinx >= 0 &&
							binx + dbinx < NBP &&
							biny + dbiny >= 0 &&
							biny + dbiny <  NBP) 
						{
							float weight = mag * abs (1 - dbinx - rbinx)
							 * abs (1 - dbiny - rbiny) * abs (1 - dbint - rbint) ;
							int index = binxo * (binx + dbinx) + binyo * (biny + dbiny) + binto * (bint + dbint); 

							ftrs[index + offset] += weight ;
						}
					}
				}
			}
		}
	}

	float total = 0; 

	FOR (i, SIFT_FEATURE_LENGTH)
	{
		total += ftrs[i+offset] * ftrs[i + offset]; 
	}

	total = sqrt(total); 
		
	FOR (i, SIFT_FEATURE_LENGTH)
	{
		ftrs[i + offset] /= (float)(total + EPSILON);
	}

	offset += SIFT_FEATURE_LENGTH; 
}


void CFeature::ComputeColorDescriptor(const Mat Img, float* ftrs, int& offset)
{	
	Scalar meanS;
	Scalar stddevS; 
	int nChn = 3; 
	
	meanStdDev(Img, meanS, stddevS);
	
	FOR (i, nChn)
	{
		ftrs[i + offset] = (float)meanS[i] / 255.0f; 
		ftrs[i + offset + nChn] = (float)stddevS[i] / 255.0f; 
	}

	offset += COLOR_FEATURE_LENGTH;
}

void CFeature::ComputeGrayHistogram(const Mat grayImg, float* ftrs, int& offset)
{
	int nBins[1] = {m_HISTBins};
	float hranges[] = {0, 256}; 
	const float* ranges[] = {hranges}; 
	Mat hist; 
	int channels[] = {0}; 
	calcHist(&grayImg,  1, channels, Mat(), hist, 1, nBins, ranges, true, false); 
	normalize(hist, hist, 1, 0, NORM_L1);
		
	FOR (i, m_HISTBins)
	{
		ftrs[i+offset] = hist.at<float>(i, 0);  
	}

	offset += m_HISTBins; 
}

void CFeature::ComputeLABHistogram(const Mat LABImg, float* ftrs, int& offset )
{
	int lenFtrs = m_LABLBins * m_LABaBins * m_LABbBins; 

	int histSize[] = {m_LABLBins, m_LABaBins, m_LABbBins};
	float ranges[] = {0, 256}; 
	const float* rangesvec[] = {ranges, ranges, ranges}; 
	MatND labHist;
	labHist.create(3, histSize, CV_32F); 
	int channels[] = {0, 1, 2}; 
	calcHist(&LABImg, 1, channels, Mat(), labHist, 3, histSize, rangesvec, true, false); 
	normalize(labHist, labHist, 1, 0, NORM_L1);

	MatIterator_<float> it = labHist.begin<float>(); 
	
	FOR (i, lenFtrs)
	{
		ftrs[i+offset] = *it; 
		it++; 
	}

	offset += lenFtrs; 
}

void CFeature::ComputeHOGDescriptor( const Mat grayImg, float* ftrs, int& offset )
{		
	CvSize winSize = cvSize(m_patchSize, m_patchSize);
	CvSize blockSize = cvSize(16, 16);
	CvSize stride = cvSize(16, 16); 
	CvSize cellSize = cvSize(16, 16);
	HOGDescriptor* hog = new HOGDescriptor(winSize, blockSize, stride, cellSize, m_HOGNBins); 
	vector<float> descriptors;
	int l = hog->getDescriptorSize();
	hog->compute(grayImg, descriptors);	
	for (int i = 0; i < m_HOGNBins; ++i) {
		double sum = 0, sum2 = 0, max = 0;
		int cnt = 0;
		for (int j = i; j < l; j += m_HOGNBins) {
			sum += descriptors[j];
			sum2 += descriptors[j] * descriptors[j];
			++cnt;
			if (descriptors[j] > max)
				max = descriptors[j];			
		}
		ftrs[offset++] = sum / cnt;
		ftrs[offset++] = sum2 / cnt - sum * sum / cnt / cnt;
		ftrs[offset++] = max;
	}
	delete hog; 
}

void CFeature::ComputeGLCMFeatures(const Mat grayImg, float* ftrs, int& offset)
{		
	for (int i = 0; i < 4; ++i) {
		glcmFeature res = glcm.GLCMFeature(grayImg, m_patchSize, i);
		ftrs[offset++] = res.dCorrelation;
		ftrs[offset++] = res.dEnergy;
		ftrs[offset++] = res.dEntropy;
		ftrs[offset++] = res.dInertiaQuadrature;
		ftrs[offset++] = res.dLocalCalm;
	}
}

void CFeature::ComputeREGIONFeatures(const Mat grayImg, float* ftrs, int& offset)
{	
	vector< vector<int> > f(m_patchSize, vector<int>(m_patchSize, 0));
	int pos = 0, neg = 0, idx = 0;
	const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
	for (int i = 0; i < m_patchSize; ++i)
		for (int j = 0; j < m_patchSize; ++j)
			if (f[i][j] == 0) {
				bool pixel = grayImg.at<uchar>(i, j) > m_REGIONThr;
				f[i][j] = ++idx;
				vector< pair<int, int> > q;
				q.push_back(make_pair(i, j));
				for (int k = 0; k < q.size(); ++k)
					for (int dir = 0; dir < 4; ++dir) {
						int x = q[k].first + dx[dir], y = q[k].second + dy[dir];
						if (x < 0 || x >= m_patchSize || y < 0 || y >= m_patchSize)
							continue;
						if (f[x][y] != 0 || (grayImg.at<uchar>(x, y) > m_REGIONThr) != pixel)
							continue;
						f[x][y] = idx;
						q.push_back(make_pair(x, y));
					}
				if (q.size() > m_REGIONBound)
					++(pixel ? pos : neg);
			}
	ftrs[offset++] = pos;
	ftrs[offset++] = neg;
}

void CFeature::NormalizeVector( float* v, int vSize) 
{      
	float a = 0.0; 
	float sqsum = 0.0;
	float mean  = 0; 

	FOR (i, vSize)
	{
		mean += v[i]; 
	}

	mean /= (float)vSize; 

	float* ptr = v;

	FOR (i, vSize)
	{
		(*ptr)  -= mean; 
		sqsum += (*ptr)*(*ptr);
		ptr++;
	}

	if(sqsum < 1e-4) 
	{
		sqsum = 1.0;
	}

	a = 1.0f/(float)(sqrt(sqsum));
	ptr = v;

	FOR (i, vSize)
	{
		(*ptr) *= a;
		ptr++;
	}    
}

//Other Tools: 
float CFeature::fast_mod_2pi(float x)
{
	while(x < 0 ) x += 2*CV_PI;
	while(x > 2*CV_PI) x -= 2*CV_PI;
	return x ;
}

void CFeature::ReadParamters(string configFileName)
{
	CConfigFile config(configFileName.c_str()); 

	FOR (i, NUM_FEATURE_TYPE)
		m_isUsedVec.push_back(false); 

	m_isUsedVec[FTRTYPE_COLOR]	= config.read<bool>("IS_USE_COLOR", false); 
	m_isUsedVec[FTRTYPE_SIFT]	= config.read<bool>("IS_USE_SIFT", false); 	
	m_isUsedVec[FTRTYPE_HIST]	= config.read<bool>("IS_USE_GREYHIST", false); 
	m_isUsedVec[FTRTYPE_HOG]	= config.read<bool>("IS_USE_HOG", false); 		
	m_isUsedVec[FTRTYPE_LAB]	= config.read<bool>("IS_USE_LAB", false); 		
	m_isUsedVec[FTRTYPE_GLCM]	= config.read<bool>("IS_USE_GLCM", false); 
	m_isUsedVec[FTRTYPE_REGION]	= config.read<bool>("IS_USE_REGION", false); 
	
	m_patchSize = config.read<int>("PATCH_SIZE", 512);
	m_trainStep = config.read<int>("TRAIN_STEP", 256);
	m_testStep = config.read<int>("TEST_STEP", 32);

	m_SIFTLayer = config.read<int>("SIFT_PYM_LAYER", 1);
	m_isAlignAngle = config.read<bool>("IS_ALIGN_ANGLE", false);
	m_HISTBins = config.read<int>("HISTGRAM_BINS", 16); 
	m_HOGCellSize = config.read<int>("HOG_CELL_SIZE", 16); 
	m_HOGNBins = config.read<int>("HOG_NUM_BINS", 9); 	 
	m_LABLBins = config.read<int>("LAB_L_BINS", 4); 
	m_LABaBins = config.read<int>("LAB_A_BINS", 7); 
	m_LABbBins = config.read<int>("LAB_B_BINS", 7);
	m_GLCMDis = config.read<int>("GLCM_DIS", 5);
	m_GLCMGrayLevel = config.read<int>("GLCM_GRAY_LEVEL", 16);	
	m_REGIONThr = config.read<int>("REGION_THR", 145);
	m_REGIONBound = config.read<int>("REGION_BOUND", 256);

	m_trainRate = config.read<int>("TRAIN_RATE", 70);
	m_testRate = config.read<int>("TEST_RATE", 30);
}

float CFeature::ComputeMainDirection(const Mat grayImg)
{
	int width = m_patchSize; 
	double angle = 0; 
	CvPoint2D32f center;
	const int nBins = 36; 
	float hist[36]; 

	center.x = width / 2.0f - 0.5f; 
	center.y = width / 2.0f - 0.5f; 

	FOR (i, 36)
	{
		hist[i] = 0.0; 
	}

	float win_w = 0; 
	float win_h = 0; 
	float W = width / 2 - 0.5f; 
	float sigma = W / 3.0f; 

	for (int w = 1; w < width-1; w++)
	{
		for (int h = 1; h < width-1; h++)
		{
			win_w = w - center.x; 
			win_h = h - center.y; 
			float r2 = win_w * win_w + win_h * win_h; 

			if (r2 < W * W + 0.5)
			{
				float gx = grayImg.at<uchar>(h, w+1) - grayImg.at<uchar>(h, w-1); 
				float gy = grayImg.at<uchar>(h+1, w) - grayImg.at<uchar>(h-1, w);
				float wgt = (float)exp(-r2 / (2 * sigma * sigma)); 
				float mag = (float)cv::sqrt(gx * gx +  gy * gy); 
				float ori = (float)fast_mod_2pi(atan2(gy, gx) + 2 * CV_PI); 
				float nt =  nBins * ori / (2*CV_PI);
				int bint = (int) floor(nt-0.5); 
				float rbint = nt - (bint+0.5); 

				FOR (dbint, 2)
				{
					int offset = 0; 
					if (bint+dbint < 0)
					{
						offset = nBins; 
					}
					int tmp = bint+dbint+offset;					
					hist[tmp % nBins] += mag * wgt * abs(1-dbint-rbint);
				}
			}
		}
	}


	FOR (iter, 6)
	{
		float prev  = hist[nBins-1] ;
		float first = hist[0] ;
		int i ;

		for (i = 0; i < nBins-1; i++)
		{
			float newh = (prev + hist[i] + hist[(i+1) % nBins]) / 3.0;
			prev = hist[i] ;
			hist[i] = newh ;
		}
		
		hist[i] = (prev + hist[i] + first)/3.0f ;
	}

	float maxh= *max_element(hist, hist+nBins); 

	int nangles = 0 ;

	FOR (i, nBins)
	{
		float h0 = hist [i] ;
		float hm = hist [(i-1+nBins) % nBins] ;
		float hp = hist [(i+1+nBins) % nBins] ;

		// is this a peak?
		if( h0 > maxh - 1e-5 && h0 > hm && h0 > hp ) {

			// quadratic interpolation
			float di = -0.5 * (hp - hm) / (hp+hm-2*h0) ;
			angle = 2*CV_PI * (i+di+0.5) / nBins ;
			break; 
		}
	}

	return angle; 
}

void CFeature::SetFtrNames(void)
{
	m_ftrNameVec.clear(); 
	m_ftrNameVec.resize(NUM_FEATURE_TYPE); 
	
	m_ftrNameVec[FTRTYPE_COLOR] = "COLOR"; 
	m_ftrNameVec[FTRTYPE_SIFT]	= "SIFT";	
	m_ftrNameVec[FTRTYPE_HIST]	= "HIST"; 	
	m_ftrNameVec[FTRTYPE_HOG]	= "HOG"; 		
	m_ftrNameVec[FTRTYPE_LAB]	= "LAB";
	m_ftrNameVec[FTRTYPE_GLCM]	= "GLCM";
	m_ftrNameVec[FTRTYPE_REGION] = "REGION";
}

string CFeature::Lowcase( string src )
{
	assert(!src.empty()); 

	transform(src.begin(), src.end(), src.begin(), tolower); 
	return src; 
}

