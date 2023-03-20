#ifndef _ADFSTEM
#define _ADFSTEM 1

#include <string>
#include <vector>
#include "atom.h"
#include "STEM.h"
using namespace std;

class ADFSTEM : public STEM
{
public:
	ADFSTEM(float E, int px, int py, int px_p, int py_p, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, float alpha_D_min, float alpha_D_max);
	float D(float kx, float ky) override;
public:
	float k_D_min, k_D_max, alpha_D_min, alpha_D_max;
};

#endif