#ifndef _DPC_COM
#define _DPC_COM 1

#include <string>
#include <vector>
#include "STEM.h"
using namespace std;

class DPC_COM : public STEM
{
public:
	DPC_COM(float E, int px, int py, int px_p, int py_p, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, float CoM_dir);
	float D(float kx, float ky) override;
public:
	int CoM;
};

#endif