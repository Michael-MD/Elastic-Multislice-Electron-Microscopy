#include "ASTEM.h"
#include "fft.h"
#include "general_purpose_utils.h"

ASTEM::ASTEM(float E, int px, int py, int px_p, int py_p, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, float alpha_min_D, float alpha_max_D)
	: STEM(E, px, py, px_p, py_p, tx, ty, tz, filename, s, Cs, deltaf, alpha_max)
{
	/*
	General class for STEM techniques involving annular detectors such as DPC, ADFSTEM, BFSTEM, ABFSTEM etc,
	*/
	this->alpha_min_D = alpha_min_D * 1e-3;
	this->alpha_max_D = alpha_max_D * 1e-3;
	this->k_min_D = this->alpha_min_D / this->lambda;
	this->k_max_D = this->alpha_max_D / this->lambda;

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


float ASTEM::D(float kx, float ky)
{
	float k = sqrt( pow(kx,2)+pow(ky,2) );
	if(k>=this->k_min_D && k<=this->k_max_D)
		return 1;
	return 0;
};

