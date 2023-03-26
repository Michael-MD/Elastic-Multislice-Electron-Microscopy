#ifndef _DPC_COM
#define _DPC_COM 1

#include <string>
#include <vector>
#include "STEM.h"
using namespace std;

class DPC_CoM : public STEM
{
public:
	DPC_CoM(float E, int px_p, int py_p, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, bool CoM_dir_x);
	float D(float kx, float ky) override;
public:
	bool CoM_dir_x;
};

#endif