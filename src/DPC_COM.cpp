#include "DPC_COM.h"
#include "STEM.h"
#include <string>
#include "fft.h"
using namespace std;

DPC_COM::DPC_COM(float E, int px, int py, int px_p, int py_p, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, float CoM)
	: STEM(E, px, py, px_p, py_p, tx, ty, tz, filename, s, Cs, deltaf, alpha_max) 
{
	this->CoM = CoM;

	// create image
	for(int i = 0; i < this->px_p; i++)
	{
		cout << '\n' << i << ' ' << endl;
		for(int j = 0; j < this->py_p; j++)
		{
			this->calcProbe(rx_p[i], ry_p[j]);
			this->propagateWaveFunctionThroughCrystal();
			irad2FFT2(this->psi_re, this->psi_im);	// diffraction pattern in far-field
			(this->I)[i][j] = this->totalIntensity(true);
		};
	};
};

float DPC_COM::D(float kx, float ky)
{
	if(this->CoM == 0) return kx;
	return ky;
};


