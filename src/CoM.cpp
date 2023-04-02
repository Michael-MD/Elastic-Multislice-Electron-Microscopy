#include "CoM.h"
#include "STEM.h"
#include <string>
#include "fft.h"
using namespace std;

CoM::CoM(float E, int px_p, int py_p, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, bool CoM_dir_x)
	: STEM(E, px, py, px_p, py_p, tx, ty, tz, filename, s, Cs, deltaf, alpha_max) 
{
	this->CoM_dir_x = CoM_dir_x;

	// create image
	for(int i = 0; i < this->px_p; i++)
	{
		cout << '\n' << i << ' ' << endl;
		for(int j = 0; j < this->py_p; j++)
		{
			this->calcProbe(rx_p[i], ry_p[j]);
			this->propagateWaveFunctionThroughCrystal();
			irad2FFT2(this->psi_re, this->psi_im);	// diffraction pattern in far-field
			(this->I)[i][j] = 1e3 * this->totalIntensity(true);
		};
	};
};

float CoM::D(float kx, float ky)
{
	if(this->CoM_dir_x) return kx;
	return ky;
};


