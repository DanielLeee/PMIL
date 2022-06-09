#pragma once

#include "config.h"
#include "Data.h"
#include "MILBoost.h"

class Solver {
public:
	enum DataType
	{
		NEG = 0,
		POS = 1,
		TEST = 2,
	};
public:
	Solver(string parafile);	
	void load(string file, DataType type);
	void clear();
	void train();
	void test(Result &res);
	~Solver();
private:		
	Data *data_pos, *data_neg, *data_test;
	MILBoost *model;	
};
