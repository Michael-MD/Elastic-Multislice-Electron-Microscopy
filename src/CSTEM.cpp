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
	// create image
	for(int i = 0; i < this->px_p; i++)
	{
		cout << '\n' << i << ' ' << endl;
		for(int j = 0; j < this->py_p; j++)
		{
			this->calcProbe(rx_p[i], ry_p[j]);
			this->propagateWaveFunctionThroughCrystal();
			irad2FFT2(this->psi_re, this->psi_im);	// diffraction pattern in far-field
			(this->I)[i][j] = this->totalIntensity(false);
		};
	};
};


