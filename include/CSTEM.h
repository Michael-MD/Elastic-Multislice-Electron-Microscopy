#ifndef _CSTEM
#define _CSTEM 1

#include <string>
#include <vector>
#include "atom.h"
#include "STEM.h"
using namespace std;

class CSTEM : public STEM
{
public:
	CSTEM(float E, int px_p, int py_p, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max);
	float D(float kx, float ky) override {return 1;};
};

#endif