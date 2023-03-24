#ifndef _ABFSTEM
#define _ABFSTEM 1

#include "ADFSTEM.h"
using namespace std;

class ABFSTEM : public ADFSTEM
{
	/*
	Implemented Annular bright field STEM by inheriting ADFSTEM. This only serves as an alias for ADFSTEM
	since ABF and ADF are the same except for the detector annular extent. 
	*/
public:
	ABFSTEM(float E, int px_p, int py_p, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, float alpha_min_D, float alpha_max_D);
};

#endif