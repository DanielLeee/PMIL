#include "Clf.h"

bool Clf::is_use_stump;
bool Clf::is_use_linear;
bool Clf::is_use_square;
bool Clf::is_use_range;

void Clf::parameter(const CConfigFile &config)
{
	is_use_stump = config.read<bool>("IS_USE_STUMP");
	is_use_linear = config.read<bool>("IS_USE_LINEAR");
	is_use_square = config.read<bool>("IS_USE_SQUARE");
	is_use_range = config.read<bool>("IS_USE_RANGE");
}

void Clf::clf_list(vector<Clf*> &clf)
{
	if (is_use_stump)
		clf.push_back(new Stump());
	if (is_use_linear)
		clf.push_back(new Linear());
	if (is_use_square)
		clf.push_back(new Square());
	if (is_use_range)
		clf.push_back(new Range());
	assert(!clf.empty());
}

Clf* Clf::train_global(const vector< vector<double> >& hist, const vector<Feature>& feature)
{	
	vector<Clf*> clf;
	clf_list(clf);
	Clf* ret = NULL;
	for (int i = 0; i < clf.size(); ++i) {		
		clf[i]->train(hist, feature);
		if (ret == NULL || clf[i]->score > ret->score) {
			if (ret != NULL)
				delete ret;
			ret = clf[i];
		}else
			delete clf[i];
	}	
	return ret;
}

Clf* Clf::from_str_global(const char *str)
{
	vector<Clf*> clf;
	clf_list(clf);
	Clf* ret = NULL;
	for (int i = 0; i < clf.size(); ++i) 
		if (ret == NULL && clf[i]->from_str(str))
			ret = clf[i];
		else
			delete clf[i];		
	return ret;	
}

void Stump::train(const vector< vector<double> >& hist, const vector<Feature>& feature)
{
	score = -inf;
	for (int i = 0; i < hist.size(); ++i) if (feature[i].avaliable()) {
		double sum = 0;
		for (int j = 0; j < hist[i].size(); ++j)
			sum += hist[i][j];
		double left = 0, right;
		for (int j = 1; j < hist[i].size(); ++j) {
			left += hist[i][j - 1];
			right = sum - left;
			double _score = left - right;
			if (abs(_score) > score) {
				score = abs(_score);
				thr = feature[i].thr(j);
				type = _score > 0;
				idx = i;				
			}			
		}
	}
}

bool Stump::from_str(const char *str)
{
	char c;
	if (sscanf(str, "Stump Ftr%d alpha=%lf [%c %lf %*c]", &idx, &alpha, &c, &thr) != 4)
		return false;
	type = (c == '+');
	return true;
}

const char* Stump::to_str(bool E)
{
	if (E) 
		sprintf(str, "Stump Ftr%4d alpha=%.9le [%c %.9le %c]", idx, alpha, type ? '+' : '-', thr, type ? '-' : '+');
	else
		sprintf(str, "Stump Ftr%4d alpha=%.5lf [%c %.5lf %c]", idx, alpha, type ? '+' : '-', thr, type ? '-' : '+');
	return str;
}

void Linear::train(const vector< vector<double> >& hist, const vector<Feature>& feature)
{
	score = -inf;
	for (int i = 0; i < hist.size(); ++i) if (feature[i].avaliable()) {
		double sum = 0, sum2 = 0;
		double sum_abs = 0, sum2_abs = 0;
		for (int j = 0; j < hist[i].size(); ++j) {
			sum += hist[i][j];
			sum2 += hist[i][j] * (feature[i].thr(j) + feature[i].thr(j + 1)) / 2;
			sum_abs += abs(hist[i][j]);
			sum2_abs += abs(hist[i][j]) * (feature[i].thr(j) + feature[i].thr(j + 1)) / 2;
		}				
		double left = 0, left2 = 0, right, right2;
		for (int j = 1; j < hist[i].size(); ++j) {			
			left += abs(hist[i][j - 1]);
			left2 += abs(hist[i][j - 1]) * (feature[i].thr(j - 1) + feature[i].thr(j)) / 2;
			right = sum_abs - left;
			right2 = sum2_abs - left2;
			double _b = feature[i].thr(j);
			double _a = sum_abs / ((left - right) * _b - left2 + right2);						
			double _score = _a * (sum2 - sum * _b);
			if (abs(_score) > score) {
				score = abs(_score);
				a = _score > 0 ? _a : -_a;
				b = _b;
				idx = i;
			}			
		}		
	}
}

bool Linear::from_str(const char *str)
{	
	return sscanf(str, "Linear Ftr%d alpha=%lf [%lf * (x - %lf)]", &idx, &alpha, &a, &b) == 4;	
}

const char* Linear::to_str(bool E)
{
	if (E)
		sprintf(str, "Linear Ftr%4d alpha=%.9le [%.9le * (x - %.9le)]", idx, alpha, a, b);
	else
		sprintf(str, "Linear Ftr%4d alpha=%.5lf [%.5lf * (x - %.5lf)]", idx, alpha, a, b);
	return str;
}

void Square::train(const vector< vector<double> >& hist, const vector<Feature>& feature)
{
	score = -inf;
	for (int i = 0; i < hist.size(); ++i) if (feature[i].avaliable()) {
		double sum_w = 0, sum_wx = 0, sum_wxx = 0;
		double sum_w_abs = 0, sum_wx_abs = 0, sum_wxx_abs = 0;		
		for (int j = 0; j < hist[i].size(); ++j) {
			double x = (feature[i].thr(j) + feature[i].thr(j + 1)) / 2, w = hist[i][j];
			sum_w += w;
			sum_wx += w * x;
			sum_wxx += w * x * x;
			sum_w_abs += abs(w);
			sum_wx_abs += abs(w) * x;
			sum_wxx_abs += abs(w) * x * x;
		}
		for (int j = 1; j < hist[i].size(); ++j) {
			double _b = feature[i].thr(j);
			double _a = sum_w_abs / (sum_wxx_abs - 2 * _b * sum_wx_abs + _b * _b * sum_w_abs);
			double _score = _a * (sum_wxx - 2 * _b * sum_wx + _b * _b * sum_w);
			if (abs(_score) > score) {
				score = abs(_score);
				a = _score > 0 ? _a : -_a;
				b = _b;
				idx = i;
			}
		}
	}	
}

bool Square::from_str(const char *str)
{	
	return sscanf(str, "Square Ftr%d alpha=%lf [%lf * sqr(x - %lf)]", &idx, &alpha, &a, &b) == 4;	
}

const char* Square::to_str(bool E)
{
	if (E)
		sprintf(str, "Square Ftr%4d alpha=%.9le [%.9le * sqr(x - %.9le)]", idx, alpha, a, b);
	else
		sprintf(str, "Square Ftr%4d alpha=%.5lf [%.5lf * sqr(x - %.5lf)]", idx, alpha, a, b);
	return str;
}

void Range::train(const vector< vector<double> >& hist, const vector<Feature>& feature)
{
	score = -inf;
	for (int i = 0; i < hist.size(); ++i) if (feature[i].avaliable()) {
		double sum = 0, left = hist[i][0];
		for (int j = 0; j < hist[i].size(); ++j)
			sum += hist[i][j];
		int min_l = 1, max_l = 1;
		double min_sum = left, max_sum = left;
		for (int j = 2; j < hist[i].size(); ++j) {
			left += hist[i][j - 1];
			if (2 * (left - min_sum) - sum > score) {
				score = 2 * (left - min_sum) - sum;
				l = feature[i].thr(min_l);
				r = feature[i].thr(j);
				type = true;
				idx = i;
			}
			if (sum - 2 * (left - max_sum) > score) {
				score = sum - 2 * (left - max_sum);
				l = feature[i].thr(max_l);
				r = feature[i].thr(j);
				type = false;
				idx = i;
			}
			if (left < min_sum) {
				min_sum = left;
				min_l = j;
			}
			if (left > max_sum) {
				max_sum = left;
				max_l = j;
			}
		}
	}
}

bool Range::from_str(const char *str)
{
	char c;
	if (sscanf(str, "Range Ftr%d alpha=%lf [%*c %lf %c %lf %*c]", &idx, &alpha, &l, &c, &r) != 5)
		return false;
	type = (c == '+');
	return true;
}

const char* Range::to_str(bool E)
{	
	if (E) 
		if (type)
			sprintf(str, "Range Ftr%4d alpha=%.9le [- %.9le + %.9le -]", idx, alpha, l, r);
		else
			sprintf(str, "Range Ftr%4d alpha=%.9le [+ %.9le - %.9le +]", idx, alpha, l, r);
	else
		if (type)
			sprintf(str, "Range Ftr%4d alpha=%.5lf [- %.5lf + %.5lf -]", idx, alpha, l, r);
		else
			sprintf(str, "Range Ftr%4d alpha=%.5lf [+ %.5lf - %.5lf +]", idx, alpha, l, r);
	return str;
}
