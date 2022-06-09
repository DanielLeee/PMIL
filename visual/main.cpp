#include "config.h"

const int MAX = 1000;

double mask[MAX][MAX];

int L, B;
int color[3];
double thr;

void read_para(string parafile)
{
	CConfigFile config(parafile);
	L = config.read<int>("PATCH_SIZE");
	B = config.read<int>("BORDER_WIDTH");
	color[0] = config.read<int>("BORDER_B");
	color[1] = config.read<int>("BORDER_G");
	color[2] = config.read<int>("BORDER_R");	
	thr = config.read<double>("THRESHOLD");
}

void draw(IplImage* img, int h1, int h2, int w1, int w2)
{
	int H = img->height, W = img->width;
	while (h1 < 0 || h2 < 0) {
		++h1;
		++h2;
	}
	while (h1 >= H || h2 >= H) {
		--h1;
		--h2;
	}
	while (w1 < 0 || w2 < 0) {
		++w1;
		++w2;
	}
	while (w1 >= W  || w2 >= W) {
		--w1;
		--w2;
	}
	printf("%d %d %d %d\n", h1, h2, w1, w2);
	for (int h = h1; h <= h2; ++h)
		for (int w = w1; w <= w2; ++w)
			for (int k = 0; k < 3; ++k)
				CV_IMAGE_ELEM(img, BYTE, h, w * 3 + k) = color[k];
}

void visual(FILE* res, IplImage* img)
{
	fscanf(res, "%*[^\n]\n");
	int h, w;
	double p;
	map<int, int> H, W;	
	vector< pair< pair<int, int>, double> > v;	
	while (fscanf(res, "(%d,%d) %lf\n", &h, &w, &p) == 3) {
		H[h] = 0;
		W[w] = 0;
		v.push_back(make_pair(make_pair(h, w), p));
	}
	h = w = 0;
	for (map<int, int>::iterator it = H.begin(); it != H.end(); ++it) 
		it->second = ++h;
	for (map<int, int>::iterator it = W.begin(); it != W.end(); ++it) 
		it->second = ++w;
	memset(mask, 0, sizeof(mask));
	for (int i = 0; i < v.size(); ++i) {
		h = H[v[i].first.first];
		w = W[v[i].first.second];
		mask[h][w] = v[i].second;
	}
	for (int i = 0; i < v.size(); ++i) {
		h = v[i].first.first;
		w = v[i].first.second;
		int hh = H[h], ww = W[w];		
		if (mask[hh][ww] < thr)
			continue;
		//if (mask[hh][ww - 1] < thr) 
			draw(img, h - (L + B) / 2, h + (L + B) / 2, w - (L + B) / 2, w - (L - B) / 2);
		//if (mask[hh][ww + 1] < thr) 
			draw(img, h - (L + B) / 2, h + (L + B) / 2, w + (L - B) / 2, w + (L + B) / 2);
		//if (mask[hh - 1][ww] < thr) 
			draw(img, h - (L + B) / 2, h - (L - B) / 2, w - (L + B) / 2, w + (L + B) / 2);
		//if (mask[hh + 1][ww] < thr) 
			draw(img, h + (L - B) / 2, h + (L + B) / 2, w - (L + B) / 2, w + (L + B) / 2);
	}
}

IplImage* merge(IplImage*& a, IplImage*& b)
{
	int w = a->width / 2, h = a->height / 2;
	IplImage* ret = cvCreateImage(cvSize(w * 2, h), IPL_DEPTH_8U, 3);
	CvRect rect = cvRect(0, 0, w, h);
	cvSetImageROI(ret, rect);
	cvResize(a, ret, CV_INTER_AREA);
	cvReleaseImage(&a);
	rect = cvRect(w, 0, w, h);
	cvSetImageROI(ret, rect);
	cvResize(b, ret, CV_INTER_AREA);
	cvReleaseImage(&b);
	cvResetImageROI(ret);
	return ret;
}

void visual(string item)
{
	FILE *res = fopen((Expr::resultData_dir + item + "." + Expr::result_ext).c_str(), "r");
	IplImage* img = cvLoadImage((Expr::image_dir + item + "." + Expr::image_ext).c_str());
	if (res != NULL && img != NULL) {		
		visual(res, img);
		IplImage* truth = cvLoadImage((Expr::truth_dir + item + "." + Expr::truth_ext).c_str());
		if (truth != NULL && img->width == truth->width && img->height == truth->height) {
			fseek(res, 0, SEEK_SET);
			visual(res, truth);
			img = merge(img, truth);
		}
		if (truth != NULL)
			cvReleaseImage(&truth);
		imwrite(Expr::resultImg_dir + item + "." + Expr::image_ext, Mat(img));
	}		
	if (res != NULL)
		fclose(res);
	if (img != NULL)
		cvReleaseImage(&img);
}

void _main(int argc, char **argv)
{
	if (argc != 2) {
		cerr << "mpiexec visual.exe expr.para" << endl;		
		return;
	}
	Tools::InitExpr(argv[1]);
	read_para(Expr::visual_para);
	vector<string> list = Tools::ListDir(Expr::resultData_dir, "*." + Expr::result_ext);
	if (Parallel::rank == 0)
		Tools::CreateDirs(Expr::resultImg_dir, list, true);
	MPI_Barrier(MPI_COMM_WORLD);
	for (int i = Parallel::rank; i < list.size(); i += Parallel::size)
		visual(list[i]);
}

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	_main(argc, argv);	
	MPI_Finalize();	
	return 0;
}
