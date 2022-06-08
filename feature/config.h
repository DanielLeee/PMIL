#pragma once

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

const double EPSILON = 1E-7; 