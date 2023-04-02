#ifndef _HRTEM
#define _HRTEM 1

#include <string>
#include <vector>
#include "atom.h"
#include "multislice.h"
using namespace std;

class HRTEM : public multislice
{
public:
	HRTEM(float E, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max);
	float D(float kx, float ky) override { return 1; };
	void calcPlaneWave();
};

#endif