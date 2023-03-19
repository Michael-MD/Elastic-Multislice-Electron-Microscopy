#ifndef _STEM
#define _STEM 1

#include <string>
#include <vector>
#include "atom.h"
#include "multislice.h"
using namespace std;

class STEM : public multislice
{
public:
	STEM(float E, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max);
	void calcProbe(float rx, float ry);
public:
	vector<vector<float>> probe_re, probe_im;
};

#endif