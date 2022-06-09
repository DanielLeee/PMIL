#include "Feature.h"

Feature::Feature(string name)
{
	this->name = name;
	lower = inf;
	upper = -inf;
	n_bins = 0;
	times = 0;
	weight = 0;
}

int Feature::index(double x) const
{
	if (!avaliable())
		return 0;	
	int idx = int(floor((x - lower) / (upper - lower) * n_bins));
	if (idx < 0)
		idx = 0;
	if (idx >= n_bins)
		idx = n_bins - 1;
	return idx;
}

double Feature::thr(int idx) const
{
	if (!avaliable())
		return (lower + upper) / 2;
	return lower + (upper - lower) / n_bins * idx;
}
