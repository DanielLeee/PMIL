#pragma once

#include "config.h"

class Sample {
public:
	Sample(const string& _name, double _score, bool _pos): name(_name), score(_score), pos(_pos) {}
	string name;
	double score;
	bool pos;
};

class Roc {	
public:
	void add(const string& name, double score, bool pos);
	void find_thr(FILE* fout, double step);
	void calculate(FILE* fout);
	void all_sample(FILE* fout);
private:
	vector<Sample> a;
};