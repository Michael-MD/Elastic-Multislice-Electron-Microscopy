#ifndef _ABFSTEM
#define _ABFSTEM 1

#include "ADFSTEM.h"
using namespace std;

class ABFSTEM : public ADFSTEM
{
public:
	ABFSTEM(float E, int px_p, int py_p, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, float alpha_min_D, float alpha_max_D);
};

#endif