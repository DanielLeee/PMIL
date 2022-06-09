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
	//��ʼ��Expr
	void InitExpr(string exprPara);
	//�����ļ��У�clear=trueʱɾ��ԭ���ļ����е�����
	void CreateDir(string dir, bool clear = false);
	//����base\item����������ļ��У�clear=trueʱɾ��ԭ���ļ����е�����
	void CreateDirs(string base, vector<string> item = vector<string>(), bool clear = false);	
	//�����ļ�������������filter(��*.jpg)���ļ����б�
	vector<string> ListDir(string path, string filter = "*.*");
	//ȥ����׺��
	string unext(string s);
	//���Ƶ����ļ��������dst����Ŀ¼�ĺϷ���
	void copy(string src, string dst);	
}
