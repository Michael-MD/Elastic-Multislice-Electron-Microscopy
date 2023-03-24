#ifndef _BFSTEM
#define _BFSTEM 1

#include "ASTEM.h"
using namespace std;

class BFSTEM : public ASTEM
{
public:
	BFSTEM(float E, int px_p, int py_p, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, float alpha_max_D);
	float D(float kx, float ky) override;
};

#endif