#ifndef _ASTEM
#define _ASTEM 1

#include <string>
#include <vector>
#include "atom.h"
#include "STEM.h"
using namespace std;

class ASTEM : public STEM
{
public:
	ASTEM(float E, int px_p, int py_p, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, float alpha_min_D, float alpha_max_D);
public:
	float alpha_min_D, alpha_max_D, k_min_D, k_max_D;
	float px_p, py_p;
};

#endif