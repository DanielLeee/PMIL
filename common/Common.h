#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

#include <cstdio>
#include <cstdarg>  
#include <ctime>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <omp.h>

#include "ConfigFile.h"
#include "mpi.h"

#pragma comment(lib, "msmpi.lib")

namespace Expr {
	void readParameters(string configFileName);	
	extern string model;
	extern string expr_dir, image_dir, feature_dir, script_dir, truth_dir, log_dir, model_dir, resultData_dir, resultImg_dir;
	extern string para_ext, image_ext, feature_ext, result_ext, truth_ext;
	extern string train_chunk_file, test_chunk_file, result_file, feature_file;
	extern string feature_para, learn_para, visual_para;	
	extern string cache_dir;
	extern int IO_limit;
	extern double roc_step;
}

namespace Parallel {
	extern int n[2]; //# of insts
	extern int N[2]; //# of bags
	extern int rank;
	extern int size;
	extern int pRecvSize;
	extern double bufd[1 << 20];
	extern int bufi[1 << 20];
	extern MPI_Status* status;
}

namespace Tools {
	//初始化Expr
	void InitExpr(string exprPara);
	//创建文件夹，clear=true时删除原有文件夹中的内容
	void CreateDir(string dir, bool clear = false);
	//创建base\item所需的所有文件夹，clear=true时删除原有文件夹中的内容
	void CreateDirs(string base, vector<string> item = vector<string>(), bool clear = false);	
	//生成文件夹下所有满足filter(如*.jpg)的文件的列表
	vector<string> ListDir(string path, string filter = "*.*");
	//去除后缀名
	string unext(string s);
	//复制单个文件，不检查dst所在目录的合法性
	void copy(string src, string dst);	
}
