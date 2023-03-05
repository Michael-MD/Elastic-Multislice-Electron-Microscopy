#include "specimen_structure.h"
#include "fft.h"
#include "fourier_utils.h"
#include "constants.h"
#include <iostream>
#include <tuple>
#include <vector>
#include "math.h"
#include "general_purpose_utils.h"

using namespace std;

vector<vector<float>> SpecimenStructure::scatteringFactor(int Z, float rx, float ry)
{

	/*
	Returns scattering amplitude f_e on reciprical space grid at the fourier coefficients.
	The formula is given in C.15 of Kirkland.
	*/
	Z--; // indexing of scattering factors is zero indexed

	vector<vector<float>> f_e(px);
	for(auto &f_ei : f_e)
		f_ei = vector<float>(py);

	float qx, qy, q2, a, b, c, d;
	auto [kx, ky] = reciprocalPoints(this->px, this->py, rx, ry);
	for(int i = 0; i < px; i++)
		for(int j = 0; j < py; j++)
		{
			qx = kx[i], qy = ky[j];
			q2 = pow(qx,2) + pow(qy,2);
			f_e[i][j] = 0.;
			for(int k = 0; k < 6; k+=2)
			{
				a = f_c[Z][0][k]; 
				b = f_c[Z][0][k+1];

				c = f_c[Z][1][k];
				d = f_c[Z][1][k+1];
				
				f_e[i][j] += a / (q2 + b) + c * exp(-d * q2);
			}
		}

	return f_e;
}