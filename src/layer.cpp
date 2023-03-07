#include "layer.h"
#include "crystal.h"
#include "fourier_utils.h"
#include "constants.h"
#include "fft.h"
#include "relativistic_corrections.h"
#include <math.h>
#include <string>
#include <fstream>
#include <tuple>
#include <vector>

#include <iostream>
using namespace std;

void layer::calcTransmissionFunction()
{
	/*
	Calculate transmission functions for each layer and store in t_re and t_im members.
	The result has been bandwidth limited appropriately.
	*/
	
	// create empty matrix structure and init. with zeros.
	vector<vector<float>> t_re(this->px_u);
	for(auto &ti : t_re)
		ti = vector<float>(this->py_u, 0.);
	t_im = t_re;
	
	// add up structure factors and assumes single layer
	for(auto atom : atoms)
	{
		auto [F_re, F_im] = atom.structureFactor();
		addMatrix(t_re, t_im, F_re, F_im);
	}

	// bandwidthLimit(this->rx_u, this->ry_u, t_re, t_im, true); // bandwidth limit v according to Kirkland
	rad2FFT2(t_re, t_im); // inverse fourier transform result, forward done to match kirkland's convention

	// multiply by constants to sigma * v
	float gamma = relativistic_mass(this->E) / me;
	float lambda = relativistic_wavelength(this->E);
	double prefac = lambda * gamma / (this->rx_u * this->ry_u);
	double tmp;
	for(long unsigned i = 0; i < t_re.size(); i++)
		for(long unsigned j = 0; j < t_re[0].size(); j++)
		{
			tmp = prefac * t_re[i][j];
			t_re[i][j] = cos(tmp);
			t_im[i][j] = sin(tmp);
		}

	bandwidthLimit(this->rx_u, this->ry_u, t_re, t_im);
	this->t_re = t_re;
	this->t_im = t_im;
}


void layer::calcFreeSpacePropagator()
{
	/*
	implements free space propogator as given in equation 6.84 in real space or 
	6.93 with second tero zero of Kirkland third edition.
	E: beam energy
	(tx, ty): unitcell tiling
	*/

	// allocate memory
	vector<vector<float>> P_re(this->px_u);
	for(auto &pi : P_re)
		pi = vector<float>(this->py_u, 0.);
	auto P_im = P_re;
	
	float c = -pi * relativistic_wavelength(E) * deltaz;
	float phi;


	auto [kx, ky] = reciprocalPoints(this->px_u, this->py_u, this->rx_u, this->ry_u);

	for(int i = 0; i < this->px_u; i++)
		for(int j = 0; j < this->py_u; j++)
		{
			phi = c * (pow(kx[i],2) + pow(ky[j],2));
			P_re[i][j] = cos(phi);
			P_im[i][j] = sin(phi);
		}

	bandwidthLimit(this->rx_u, this->ry_u, P_re, P_im);
	this->P_re = P_re;
	this->P_im = P_im;
}