#include "CSTEM.h"
#include "fft.h"
#include "general_purpose_utils.h"

CSTEM::CSTEM(float E, int px, int py, int px_p, int py_p, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max)
	: STEM(E, px, py, px_p, py_p, tx, ty, tz, filename, s, Cs, deltaf, alpha_max)
{
	/*
	CSTEM
	*/
};


