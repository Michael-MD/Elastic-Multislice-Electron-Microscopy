#include "ADFSTEM.h"
#include "ASTEM.h"

ADFSTEM::ADFSTEM(float E, int px, int py, int px_p, int py_p, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, float alpha_min_D, float alpha_max_D)
	: ASTEM(E, px, py, px_p, py_p, tx, ty, tz, filename, s, 
		Cs, deltaf, alpha_max, alpha_min_D, alpha_max_D) {};
