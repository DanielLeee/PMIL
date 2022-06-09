#pragma once

#include "config.h"
#include "Data.h"
#include "Feature.h"
#include "Clf.h"

class Result {
public:
	class Patch {
	public:
		Patch(int _x, int _y, double _score): x(_x), y(_y), score(_score) {}
		int x, y;
		double score;
	};
public:
	vector<double> bag;
	vector< vector<Patch> > inst;
};

class MILBoost {
public:
	MILBoost(string parafile);
	static void softmax(double& a, double b);
	void train(const Data* neg, const Data* pos);
	void test(const Data* data, Result &res);
	void to_file();
	void from_file();
	void clear();
	~MILBoost();
private:
	int print(const char* format, ...);
public:
	vector<Feature> feature;	
	vector<Clf*> weak_clf;
private:
	int T, n_bins, alpha_bins;	
	double alpha_bound;
	string clf_file, log_file;
	FILE* log_fout;
};
