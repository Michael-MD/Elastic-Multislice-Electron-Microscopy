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


STEM::STEM(float E, int px, int py, int px_p, int py_p, int tx, int ty, int tz, string filename, vector<float> &s,
			float Cs, float deltaf, float alpha_max)
	: multislice(E, px, py, tx, ty, tz, filename, s)
{
	/*
	calculates STEM image on px x py grid where the intensity at each position is calculated by
	propagating the stem probe using the same resolution.
	*/
	this->Cs = Cs;
	this->deltaf = deltaf;
	this->alpha_max = alpha_max;

	this->px_p = px_p;
	this->py_p = py_p;

	// initilize intensity and Img arrays
	vector<vector<float>> I(this->px_p);
	for(auto &Ii : I)
		Ii = vector<float>(this->py_p);

	// make list of probe positions
	vector<float> rx_p(this->px_p);
	for(int i = 0; i < this->px_p; i++)
		rx_p[i] = this->rx * i / this->px_p;
	
	vector<float> ry_p(this->py_p);
	for(int i = 0; i < this->py_p; i++)
		ry_p[i] = this->ry * i / this->py_p;

	// create image
	for(int i = 0; i < this->px_p; i++)
	{
		cout << '\n' << i << ' ';
		for(int j = 0; j < this->py_p; j++)
		{
			this->calcProbe(rx_p[i], ry_p[j]);
			this->propagateWaveFunctionThroughCrystal();
			irad2FFT2(this->psi_re, this->psi_im);	// diffraction pattern in far-field
			I[i][j] = this->totalIntensity();
		}
	}
	this->I = I;
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
			this->psi_im[i][j] = sin(arg);
		}

	handamardProduct(this->psi_re, this->psi_im, this->H0_re, this->H0_im);


	/*
	Finds normalization constant using plancherell theorem which states the intensity in real and
	reciprical space are the same except in reciprical space there is a factor of 1/N**2. This factor
	is conveniently the differential area element in reciprical space.
	*/
	float Ap = 1 / this->totalIntensity();
	for(int i = 0; i < this->px; i++)
		for(int j = 0; j < this->py; j++)
		{
			this->psi_re[i][j] *= Ap;
			this->psi_im[i][j] *= Ap;
		}

	rad2FFT2(this->psi_re, this->psi_im);
};
