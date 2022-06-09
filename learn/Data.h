#pragma once

#include "config.h"

class Data {
public:	
	Data(int Dims);	
	~Data();
	void load(FILE* fin, bool train);	
	double operator()(int i, int j) const;
	double* operator()(int i) const;
	void clear();
public:
	int NBag, NInst, Dims;
	vector<int> bag;
	vector< pair<int, int> > pos;
private:
	vector<double*> data;	
};

