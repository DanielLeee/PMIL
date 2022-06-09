#pragma once

#include "config.h"

class Feature {
	friend class MILBoost;
public:
	Feature(string name);	
	bool avaliable() const { return upper - lower > eps; }
	int index(double val) const;
	double thr(int index) const;
private:
	string name;
	double lower, upper, weight;
	int n_bins, times;	
};
