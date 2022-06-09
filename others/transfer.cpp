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

bool transfer(string src, string dst)
{
	IplImage* img = cvLoadImage(src.c_str());
	if (img == NULL || img->height != 10000 || img->width != 10000) {
		cvReleaseImage(&img);
		return false;
	}
	IplImage* ret = cvCreateImage(cvSize(256, 256), IPL_DEPTH_8U, 3);
	cvResize(img, ret);
	imwrite(dst, Mat(ret));
	cvReleaseImage(&img);
	cvReleaseImage(&ret);
	return true;
}

int _main(int argc, char **argv)
{
	MPI_Comm_size(MPI_COMM_WORLD, &Parallel::size);
	MPI_Comm_rank(MPI_COMM_WORLD, &Parallel::rank);
	string src(argv[1]), dst(argv[2]);	
	if (src.back() != '\\');
		src += "\\";
	if (dst.back() != '\\');
		dst += "\\";
	vector<string> list = Tools::ListDir(src, "*.jpg");
	if (Parallel::rank == 0)
		Tools::CreateDirs(dst, list, true);
	MPI_Barrier(MPI_COMM_WORLD);
	char buf[MAX_PATH];
	sprintf(buf, "log\\%d.txt", Parallel::rank);
	FILE* log = fopen(buf, "w");
	for (int i = Parallel::rank; i < list.size(); i += Parallel::size) {
		bool ret = transfer(src + list[i] + ".jpg", dst + list[i] + ".jpg");
		fprintf(log, "%s %s\n", ret ? "success" : "failed", list[i].c_str());
		fflush(log);
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
