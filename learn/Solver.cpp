#include "Solver.h"

Solver::Solver(string parafile)
{						
	model = new MILBoost(parafile);
	data_pos = new Data(model->feature.size());
	data_neg = new Data(model->feature.size());	
	data_test = new Data(model->feature.size());
}

void Solver::load(string file, DataType type)
{	
	FILE* fin = fopen(file.c_str(), "r");
	(type == TEST ? data_test : (type == POS ? data_pos : data_neg))->load(fin, type != TEST);
	fclose(fin);
}

void Solver::clear()
{
	data_pos->clear();
	data_neg->clear();
	data_test->clear();
}

void Solver::train()
{
	model->train(data_neg, data_pos);
	model->to_file();
}

void Solver::test(Result &res)
{
	if (model->weak_clf.empty())
		model->from_file();
	model->test(data_test, res);	
}

Solver::~Solver()
{	
	clear();
	delete model;
}
