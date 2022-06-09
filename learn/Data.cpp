#include "Data.h"

Data::Data(int Dims)
{
	this->Dims = Dims;
	NBag = NInst = 0;	
}

Data::~Data()
{			
	clear();	
}

void Data::load(FILE* fin, bool train)
{
	++NBag;
	char buf[MAX_PATH];
	int x, y;
	while (fscanf(fin, "%s %d %d", buf, &x, &y) == 3)
		if (!train || strcmp(buf, "train") == 0) {
			++NInst;
			double* arr = new double[Dims];
			data.push_back(arr);
			for (int i = 0; i < Dims; ++i)
				fscanf(fin, "%*d:%lf", arr + i);						
			bag.push_back(NBag - 1);
			pos.push_back(make_pair(x, y));
		}else 
			fscanf(fin, "%*[^\n]\n");
}

double Data::operator()(int i, int j) const
{	
	return data[i][j];
}

double* Data::operator()(int i) const
{
	return data[i];
}

void Data::clear()
{
	for (int i = 0; i < NInst; ++i)
		delete data[i];
	NBag = NInst = 0;
	data.clear();
	bag.clear();
	pos.clear();
}