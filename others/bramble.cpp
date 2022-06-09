#include "Common.h"
#ifdef _DEBUG
#pragma comment(lib, "commond.lib")
#else
#pragma comment(lib, "common.lib")
#endif

#include "FreeImage.h"
#include "opencv\cv.h"
#include "opencv\highgui.h"
using namespace cv;

#ifdef _DEBUG
#pragma comment(lib, "FreeImaged.lib")
#pragma comment(lib,"opencv_core242d.lib")            // opencv_core
#pragma comment(lib,"opencv_imgproc242d.lib")        // opencv_imgproc
#pragma comment(lib,"opencv_highgui242d.lib")        // opencv_highgui
#pragma comment(lib,"opencv_objdetect242d.lib")    // opencv_objdetect
#pragma comment(lib,"opencv_features2d242d.lib")    // opencv_features2d
#else
#pragma comment(lib, "FreeImage.lib")
#pragma comment(lib,"opencv_core242.lib")            // opencv_core
#pragma comment(lib,"opencv_imgproc242.lib")        // opencv_imgproc
#pragma comment(lib,"opencv_highgui242.lib")        // opencv_highgui
#pragma comment(lib,"opencv_objdetect242.lib")    // opencv_objdetect
#pragma comment(lib,"opencv_features2d242.lib")    // opencv_features2d
#endif

void conv(string src, string dst)
{
	IplImage* img = cvLoadImage(src.c_str());
	IplImage* rst = cvCreateImage(cvSize(img->width / 10, img->height / 10), IPL_DEPTH_8U, 3);
	cvResize(img, rst, CV_INTER_AREA);
	cvSaveImage(dst.c_str(), rst);
	cvReleaseImage(&img);
	cvReleaseImage(&rst);
}

int _main(int argc, char **argv)
{
	MPI_Comm_size(MPI_COMM_WORLD, &Parallel::size);
	MPI_Comm_rank(MPI_COMM_WORLD, &Parallel::rank);
	Expr::readParameters(argv[1]);
	vector<string> list = Tools::ListDir(Expr::image_dir + "pos", "*.jpg");
	for (int i = list.size(); i; --i)
		swap(list[i - 1], list[rand() % i]);
	for (int i = 0; i < list.size() / 2; ++i) {
		char buf[MAX_PATH];
		sprintf(buf, "1_%d_s.png", i + 1);
		conv(Expr::image_dir + "pos\\" + list[i] + "." + Expr::image_ext, Expr::expr_dir + "Bramble\\TrainingImages\\Images\\" + string(buf));		
	}
	for (int i = 0; i < list.size() / 2; ++i) {
		char buf[MAX_PATH];
		sprintf(buf, "1_%d_s_GT.png", i + 1);
		conv(Expr::truth_dir + "pos\\" + list[i] + "." + Expr::truth_ext, Expr::expr_dir + "Bramble\\TrainingImages\\GT\\" + string(buf));		
	}
	for (int i = list.size() / 2; i < list.size(); ++i) {
		char buf[MAX_PATH];
		sprintf(buf, "1_%d_s.png", i - list.size() / 2 + 1);
		conv(Expr::image_dir + "pos\\" + list[i] + "." + Expr::image_ext, Expr::expr_dir + "Bramble\\TestImages\\Images\\" + string(buf));		
	}
	for (int i = list.size() / 2; i < list.size(); ++i) {
		char buf[MAX_PATH];
		sprintf(buf, "1_%d_s_GT.png", i - list.size() / 2 + 1);
		conv(Expr::truth_dir + "pos\\" + list[i] + "." + Expr::truth_ext, Expr::expr_dir + "Bramble\\TestImages\\GT\\" + string(buf));		
	}

	return 0;
}

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	_main(argc, argv);	
	MPI_Finalize();	
	return 0;
}
