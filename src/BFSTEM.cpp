#include "BFSTEM.h"
#include "ASTEM.h"

BFSTEM::BFSTEM(float E, int px, int py, int px_p, int py_p, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, float alpha_max_D)
	: ASTEM(E, px, py, px_p, py_p, tx, ty, tz, filename, s, 
		Cs, deltaf, alpha_max, 0, alpha_max_D) {};

float BFSTEM::D(float kx, float ky)
{
	float k = sqrt( pow(kx,2)+pow(ky,2) );
	if(k>=this->k_min_D && k<=this->k_max_D)
		return 1;
	return 0;
};