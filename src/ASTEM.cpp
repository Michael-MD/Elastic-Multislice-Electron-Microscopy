
#include "ASTEM.h"
#include "fft.h"
#include "general_purpose_utils.h"

ASTEM::ASTEM(float E, int px, int py, int px_p, int py_p, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, float alpha_min_D, float alpha_max_D)
	: STEM(E, px, py, px_p, py_p, tx, ty, tz, filename, s, Cs, deltaf, alpha_max)
{
	this->alpha_min_D = alpha_min_D * 1e-3;
	this->alpha_max_D = alpha_max_D * 1e-3;
	this->k_min_D = this->alpha_min_D / this->lambda;
	this->k_max_D = this->alpha_max_D / this->lambda;

	this->px_p = px_p;
	this->py_p = py_p;

	// create image
	for(int i = 0; i < this->px_p; i++)
	{
		cout << '\n' << i << ' ' << endl;
		for(int j = 0; j < this->py_p; j++)
		{
			// cout << j << ' ';
			this->calcProbe(rx_p[i], ry_p[j]);
			// writeToFile("probe_re.txt", this->psi_re);
			// writeToFile("probe_im.txt", this->psi_im);
			// char s;
			// cout << 'c' << endl;
			// cin >> s;
			this->propagateWaveFunctionThroughCrystal();
			// writeToFile("probe_re.txt", this->psi_re);
			// writeToFile("probe_im.txt", this->psi_im);
			// cout << 'd' << endl;
			// cin >> s;
			irad2FFT2(this->psi_re, this->psi_im);	// diffraction pattern in far-field
			// writeToFile("probe_re.txt", this->psi_re);
			// writeToFile("probe_im.txt", this->psi_im);
			// cout << 'e' << endl;
			// cin >> s;
			(this->I)[i][j] = this->totalIntensity();
			// writeToFile("probe_re.txt", this->psi_re);
			// writeToFile("probe_im.txt", this->psi_im);
			// cout << 'f' << endl;
			// cin >> s;
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