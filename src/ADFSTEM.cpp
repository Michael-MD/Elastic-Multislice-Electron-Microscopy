#include "STEM.h"
#include "ADFSTEM.h"
#include "constants.h"
#include "math.h"
#include <math.h>
#include <string>
#include <tuple>
#include "general_purpose_utils.h"
#include "fourier_utils.h"
#include "fft.h"
using namespace std;

ADFSTEM::ADFSTEM(float E, int px, int py, int px_p, int py_p, int tx, int ty, int tz, string filename, vector<float> &s,
			float Cs, float deltaf, float alpha_max, float alpha_D_min, float alpha_D_max)
	: STEM(E, px, py, px_p, py_p, tx, ty, tz, filename, s, Cs, deltaf, alpha_max)
{
	this->alpha_D_min = alpha_D_min * 1e-3;
	this->alpha_D_max = alpha_D_max * 1e-3;

	this->k_D_min = this->alpha_D_min / this->lambda;
	this->k_D_max = this->alpha_D_max / this->lambda;
}


float ADFSTEM::D(float kx, float ky)
{
	float k = sqrt( pow(kx,2) + pow(ky,2) );
	if(k > this->k_D_min && k < k_D_max) return 1;
	else return 0;
}