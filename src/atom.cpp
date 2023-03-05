#include "atom.h"
#include "fft.h"
#include "fourier_utils.h"
#include "constants.h"
#include <iostream>
#include <tuple>
#include <vector>
#include "math.h"
#include "general_purpose_utils.h"
#include <complex>

using namespace std;

vector<vector<float>> Atom::scatteringFactor()
{

	/*
	Returns scattering amplitude f_e on reciprical space grid at the fourier coefficients.
	The formula is given in C.15 of Kirkland.
	*/

	int Z = this->Z; 
	Z--;	// indexing of scattering factors is zero indexed

	vector<vector<float>> f_e(this->px);
	for(auto &f_ei : f_e)
		f_ei = vector<float>(this->py);

	float qx, qy, q2, a, b, c, d;
	auto [kx, ky] = reciprocalPoints(this->px, this->py, this->rx, this->ry);
	for(int i = 0; i < this->px; i++)
		for(int j = 0; j < this->py; j++)
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

tuple<vector<vector<float>>,vector<vector<float>>> Atom::structureFactor()
{
	/*
	Calculates structure factor, equation given by Kirkland 5.23.
	*/
	auto f_e = this->scatteringFactor();
	auto F_re = f_e, F_im = f_e;

	float qx, qy, c;
	float x = this->xf * this->rx, y = this->yf * this->ry;
	auto [kx, ky] = reciprocalPoints(this->px, this->py, this->rx, this->ry);

	for(int i = 0; i < px; i++)
		for(int j = 0; j < py; j++)
		{
			qx = kx[i], qy = ky[j];
			c = pi2 * (qx*x + qy*y);
			F_re[i][j] *= cos(c);
			F_im[i][j] *= sin(c);
		}

	return {F_re, F_im};
}

void Atom::calcPotenial()
{
	/*
	Calculates specimen potential in real space by iFFT eq. 5.21 of Kirkland. 
	Result returned in Ang * kg-Ang^2 / s^2 which is a unit of energy times Ang. Recall, [J] = kg m^2/s^2.
	*/
	auto [Fre, Fim] = this->structureFactor();
	irad2FFT2(Fre,Fim);
	// Since the FFT is linear, we may now multiply by the additional constant which defines the potential
	float c = pow(h,2) / (2*pi * me * this->rx * this->ry);
	for(auto &Fi : Fre)
		for(auto &Fij : Fi)
			Fij *= c;
	this->v = Fre;
}
