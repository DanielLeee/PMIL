#include "Common.h"

namespace Expr {
	void readParameters(string configFileName)
	{
		CConfigFile config(configFileName);

		expr_dir = config.read<string>("EXPR");
		model = config.read<string>("MODEL");
		image_dir = config.read<string>("IMAGE");
		feature_dir = config.read<string>("FEATURE");
		script_dir = config.read<string>("SCRIPT");	
		truth_dir = config.read<string>("TRUTH");
		log_dir = config.read<string>("LOG");	
		resultData_dir = config.read<string>("RESULTDATA");
		resultImg_dir = config.read<string>("RESULTIMAGE");
	
		if (expr_dir.back() != '\\')
			expr_dir += "\\";
		model_dir = expr_dir + model + "\\";
		image_dir = expr_dir + image_dir + "\\";
		feature_dir = expr_dir + feature_dir + "\\";
		truth_dir = expr_dir + truth_dir + "\\";
		script_dir = expr_dir + script_dir + "\\";		
		log_dir = expr_dir + log_dir + "\\";	
		resultData_dir = model_dir + resultData_dir + "\\";
		resultImg_dir = model_dir + resultImg_dir + "\\";

		para_ext = config.read<string>("PARA_EXT");
		image_ext = config.read<string>("IMAGE_EXT");
		feature_ext = config.read<string>("FEATURE_EXT");
		result_ext = config.read<string>("RESULT_EXT");	
		truth_ext = config.read<string>("TRUTH_EXT");	

		train_chunk_file = script_dir + config.read<string>("TRAIN");
		test_chunk_file = script_dir + config.read<string>("TEST");	
		result_file = model_dir + config.read<string>("RESULT");
		feature_file = script_dir + config.read<string>("FEALIST");
	
		feature_para = configFileName + "\\..\\" + config.read<string>("FEATURE_PARA") + "." + para_ext;
		learn_para = configFileName + "\\..\\" + config.read<string>("LEARN_PARA") + "." + para_ext;
		visual_para = configFileName + "\\..\\" + config.read<string>("VISUAL_PARA") + "." + para_ext;

		IO_limit = config.read<int>("IO_LIMIT");
		cache_dir = config.read<string>("CACHE_DIR");
		if (cache_dir.back() != '\\')
			cache_dir += "\\";

		roc_step = config.read<double>("ROC_STEP");
	}
	string model;
	string expr_dir, image_dir, feature_dir, script_dir, truth_dir, log_dir, model_dir, resultData_dir, resultImg_dir;
	string para_ext, image_ext, feature_ext, result_ext, truth_ext;
	string train_chunk_file, test_chunk_file, result_file, feature_file;
	string feature_para, learn_para, visual_para;	
	string cache_dir;
	int IO_limit;
	double roc_step;
}

namespace Parallel {
	int n[2];
	int N[2];
	int rank;
	int size;
	int pRecvSize;
	double bufd[1 << 20];
	int bufi[1 << 20];
	MPI_Status* status = new MPI_Status;
}

namespace Tools {
	void InitExpr(string ExprPara)
	{
		//Init
		MPI_Comm_size(MPI_COMM_WORLD, &Parallel::size);
		MPI_Comm_rank(MPI_COMM_WORLD, &Parallel::rank);
		Expr::readParameters(ExprPara);
		//Dirs
		if (Parallel::rank == 0) {
			Tools::CreateDir(Expr::model_dir, false);
			Tools::CreateDir(Expr::image_dir, false);
			Tools::CreateDir(Expr::feature_dir, false);
			Tools::CreateDir(Expr::image_dir, false);
			Tools::CreateDir(Expr::script_dir, false);
			Tools::CreateDir(Expr::log_dir, false);
			Tools::CreateDir(Expr::resultData_dir, false);
			Tools::CreateDir(Expr::resultImg_dir, false);
			Tools::CreateDir(Expr::cache_dir, false);
		}
		MPI_Barrier(MPI_COMM_WORLD);
		//Log	
		#ifndef _DEBUG
		char output[MAX_PATH];
		sprintf(output, "%s%d.txt", Expr::log_dir.c_str(), Parallel::rank);	
		freopen(output, "w", stdout);
		#endif
	}	

	void CreateDir(string dir, bool clear)
	{
		if (_access(dir.c_str(), 0) == -1)		
			_mkdir(dir.c_str()); 
		else
			if (clear)
				system(("del /F /S /Q " + dir).c_str());
	}

	void CreateDirs(string base, vector<string> item, bool clear)
	{
		if (base.back() != '\\')
			base += "\\";
		for (int i = 0; i < base.size(); ++i)
			if (base[i] == '\\')
				CreateDir(base.substr(0, i));	
		set<string> Dirs;
		Dirs.insert("");		
		for (int i = 0; i < item.size(); ++i)
			for (int j = 0; j < item[i].size(); ++j)
				if (item[i][j] == '\\')
					Dirs.insert(item[i].substr(0, j));
		for (set<string>::iterator it = Dirs.begin(); it != Dirs.end(); ++it)
			CreateDir(base + (*it), clear);
	}

	void find(string path, string filter, vector<string> &ret)
	{
		if (path.back() != '\\')
			path += "\\";
		WIN32_FIND_DATA FindFileData;		
		HANDLE hFind = ::FindFirstFile((path + "*.*").c_str(), &FindFileData);
		if(hFind == INVALID_HANDLE_VALUE)
			return;
		do {
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {		
				if(FindFileData.cFileName[0] != '.')		
					find(path + FindFileData.cFileName, filter, ret);			
			}
		}while (FindNextFile(hFind,&FindFileData));	
		FindClose(hFind);
		hFind = ::FindFirstFile((path + filter).c_str(), &FindFileData);
		if(hFind == INVALID_HANDLE_VALUE)
			return;
		do {
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {				
			}else {				
				string fileName = FindFileData.cFileName;			
				ret.push_back(path + fileName);
			}
		}while (FindNextFile(hFind,&FindFileData));	
		FindClose(hFind);
	}

	vector<string> ListDir(string dir, string filter)
	{
		vector<string> ret;
		find(dir, filter, ret);
		for (int i = 0; i < ret.size(); ++i)
			ret[i] = unext(ret[i].substr(dir.size()));
		sort(ret.begin(), ret.end());
		return ret;
	}

	string unext(string s)
	{
		for (int i = s.size() - 1; i >= 0; --i)
			if (s[i] == '.')
				return s.substr(0, i);
		return s;
	}

	void copy(string src, string dst)
	{
		system(("copy \"" + src + "\" \"" + dst + "\" /Z /Y >NUL").c_str());		
	}
}
