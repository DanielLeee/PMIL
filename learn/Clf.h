#pragma once

#include "config.h"
#include "Feature.h"

class Clf {
	friend class MILBoost;
public:
	static void parameter(const CConfigFile &config);
	static void clf_list(vector<Clf*> &clf);
	static Clf* train_global(const vector< vector<double> >& hist, const vector<Feature>& feature);
	static Clf* from_str_global(const char *str);
public:
	static bool is_use_stump;
	static bool is_use_linear;
	static bool is_use_square;
	static bool is_use_range;
public:
	Clf(): idx(-1), score(0), alpha(1) {}
	double operator()(double *p) { return alpha * (*this)(p[idx]); }
	virtual double operator()(double x) = 0;
	virtual void train(const vector< vector<double> >& hist, const vector<Feature>& feature) = 0;
	virtual bool from_str(const char *str) = 0;
	virtual const char* to_str(bool E = false) = 0;
public:
	char str[MAX_PATH];
	int idx;
	double score, alpha;
};

class Stump : public Clf {	
public:
	Stump(): thr(0), type(false) {}
	virtual double operator()(double x) { return ((x < thr) != type) ? -1 : 1; };
	virtual void train(const vector< vector<double> >& hist, const vector<Feature>& feature);		
	virtual bool from_str(const char *str);
	virtual const char* to_str(bool E = false);	
private:
	double thr;
	bool type; // ture: -/+, false: +/-
};

class Linear : public Clf {
public:
	Linear(): a(0), b(0) {}
	virtual double operator()(double x) { return a * (x - b); };
	virtual void train(const vector< vector<double> >& hist, const vector<Feature>& feature);		
	virtual bool from_str(const char *str);
	virtual const char* to_str(bool E = false);	
private:
	double a, b;
};

class Square : public Clf {
public:
	Square(): a(0), b(0) {}
	virtual double operator()(double x) { return a * (x - b) * (x - b); };
	virtual void train(const vector< vector<double> >& hist, const vector<Feature>& feature);		
	virtual bool from_str(const char *str);
	virtual const char* to_str(bool E = false);	
private:
	double a, b;
};

class Range : public Clf {	
public:
	Range(): l(0), r(0), type(false) {}
	virtual double operator()(double x) { return (x >= l && x <= r) != type ? -1 : 1; };
	virtual void train(const vector< vector<double> >& hist, const vector<Feature>& feature);		
	virtual bool from_str(const char *str);
	virtual const char* to_str(bool E = false);	
private:
	double l, r;
	bool type;
};
