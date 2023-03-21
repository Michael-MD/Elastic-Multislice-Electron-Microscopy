#ifndef _CTEM
#define _CTEM 1

#include <string>
#include <vector>
#include "atom.h"
#include "multislice.h"
#include <iostream>
using namespace std;

class CTEM : public multislice
{
public:
	CTEM(float E, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max);
	void calcPlaneWave();
	float D(float kx, float ky) override { cout << 'a'; return 1; };
};

#endif