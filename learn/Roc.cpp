#include "Roc.h"

bool operator<(const Sample &a, const Sample &b) { return a.score < b.score; }

void Roc::add(const string& name, double score, bool pos)
{
	if (score < 0)
		score = 0;
	if (score > 1)
		score = 1;
	a.push_back(Sample(name, score, pos));
}

void Roc::find_thr(FILE* fout, double step)
{
	double best_thr, best_F = -inf;
	for (double thr = step; thr < 1; thr += step) {
		int cnt[2][2] = {0, 0, 0, 0};
		for (int i = 0; i < a.size(); ++i)
			++cnt[a[i].pos][a[i].score > thr];
		double P = double(cnt[1][1]) / (cnt[0][1] + cnt[1][1]);
		double R = double(cnt[1][1]) / (cnt[1][0] + cnt[1][1]);
		double F = 2 * P * R / (P + R);
		if (F > best_F) {
			best_F = F;
			best_thr = thr;
		}
	}	
	fprintf(fout, "Best thr = %.5lf\n", best_thr);
	int cnt[2][2] = {0, 0, 0, 0};
	for (int i = 0; i < a.size(); ++i)
		++cnt[a[i].pos][a[i].score > best_thr];	
	fprintf(fout, "truth\\pre   +       -\n");
	fprintf(fout, "+\t%5d\t%5d\n", cnt[1][1], cnt[1][0]);
	fprintf(fout, "-\t%5d\t%5d\n", cnt[0][1], cnt[0][0]);
	double P = double(cnt[1][1]) / (cnt[0][1] + cnt[1][1]);
	double R = double(cnt[1][1]) / (cnt[1][0] + cnt[1][1]);
	double F = 2 * P * R / (P + R);
	fprintf(fout, "Precision = %.5lf Recall = %.5lf F-measure = %.5lf\n", P, R, F);
}

void Roc::calculate(FILE* fout)
{
	sort(a.begin(), a.end());
	reverse(a.begin(), a.end());
	double s = 0, ap = 0;
	for (int i = 0; i < a.size(); ++i) 
		if (a[i].pos) {
			++s;
			ap += s / (i + 1);
		}
	fprintf(fout, "Average Precision = %.5lf\n", ap / s);
	reverse(a.begin(), a.end());
	int neg = 0, pos = 0;
	double area = 0;
	for (int i = 0; i < a.size(); ++i)
		if (a[i].pos) {
			area += neg;
			++pos;
		}else
			++neg;
	if (pos != 0 && neg != 0) {
		area = area / pos / neg;
		double q1 = area / (2 - area), q2 = 2 * sqr(area) / (1 + area);
		double v = area * (1 - area) + (pos - 1) * (q1 - sqr(area)) + (neg - 1) * (q2 - sqr(area));
		v = v / pos / neg;
		fprintf(fout, "Area below Roc-curve = %.5lf [variance = %.5lf]\n", area, v);
	}else 
		fprintf(fout, "All %s\n", pos == 0 ? "pos" : "neg");
}

void Roc::all_sample(FILE* fout)
{
	for (int i = 0; i < a.size(); ++i)
		fprintf(fout, "%c %.9lf %s\n", a[i].pos ? '+' : '-', a[i].score, a[i].name.c_str());
}
