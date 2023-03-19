#include "STEM.h"
#include "multislice.h"
#include "constants.h"
#include <vector>
#include <string>
#include <tuple>
#include "general_purpose_utils.h"
#include "fourier_utils.h"
#include "fft.h"
using namespace std;


STEM::STEM(float E, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s,
			float Cs, float deltaf, float alpha_max)
	: multislice(E, px, py, tx, ty, tz, filename, s)
{
	this->Cs = Cs;
	this->deltaf = deltaf;
	this->alpha_max = alpha_max;
};


void STEM::calcProbe(float rx_p, float ry_p)
{
	/*
	Calculates probe wave function at position rx, ry and places result in probe_re, probe_im.
	*/
	calcLensTF(this->Cs, this->deltaf, this->alpha_max);
	auto [kx, ky] = reciprocalPoints(this->px, this->py, this->rx, this->ry);

	float arg;
	for(int i = 0; i < this->px; i++)
		for(int j = 0; j < this->py; j++)
		{
			arg = pi2 * (kx[i]*rx_p + ky[j]*ry_p);
			this->psi_re[i][j] = cos(arg);
			this->psi_re[i][j] = sin(arg);
		}

	handamardProduct(this->psi_re, this->psi_im, this->H0_re, this->H0_im);
	rad2FFT2(this->psi_re, this->psi_im);

	float Ap; // normalization constant

	writeToFile("probe_re", this->psi_re);
	writeToFile("probe_im", this->psi_im);
}

// void STEM::calcPsi0()
// {
// 	/*
// 	Creates initial wave function probe using equation 5.48 of kirkland.
// 	*/

	
// }
