#include "layer.h"
#include "crystal.h"
#include "fourier_utils.h"
#include "constants.h"
#include "fft.h"
#include "relativistic_corrections.h"
#include "general_purpose_utils.h"
#include <math.h>
#include <string>
#include <fstream>
#include <tuple>
#include <vector>

#include <iostream>
using namespace std;

layer::layer(float E, int px_u, int py_u, float rx_u, float ry_u, int tx, int ty, float deltaz) 
	{
		this->E = E;
		this->px_u = px_u;
		this->py_u = py_u;
		this->px = px_u * tx;
		this->py = py_u * ty;

		this->rx_u = rx_u;
		this->ry_u = ry_u;
		this->rx = rx_u * tx;
		this->ry = ry_u * ty;

		this->tx = tx;
		this->ty = ty;

		this->deltaz = deltaz;
	};


void layer::calcTransmissionFunction()
{
	/*
	Calculate transmission functions for each layer and store in t_re_u and t_im_u members.
	The result has been bandwidth limited appropriately.
	*/
	
	// create empty matrix structure and init. with zeros.
	vector<vector<float>> t_re_u(this->px_u);
	for(auto &ti : t_re_u)
		ti = vector<float>(this->px_u, 0.);
	t_im_u = t_re_u;
	
	// add up structure factors and assumes single layer
	for(auto atom : atoms)
	{
		auto [F_re, F_im] = atom.structureFactor();
		addMatrix(t_re_u, t_im_u, F_re, F_im);
	}

	// bandwidthLimit(this->rx_u, this->ry_u, t_re_u, t_im_u, true); // bandwidth limit v according to Kirkland
	rad2FFT2(t_re_u, t_im_u); // inverse fourier transform result, forward done to match kirkland's convention

	// multiply by constants to sigma * v
	float gamma = relativistic_mass(this->E) / me;
	float lambda = relativistic_wavelength(this->E);
	double prefac = lambda * gamma / (this->rx * this->ry); 	// kirkland makes mistake here in Fig 5.11
	double tmp;
	for(long unsigned i = 0; i < t_re_u.size(); i++)
		for(long unsigned j = 0; j < t_re_u[0].size(); j++)
		{
			tmp = prefac * t_re_u[i][j];
			t_re_u[i][j] = cos(tmp);
			t_im_u[i][j] = sin(tmp);
		}

	this->t_re_u = t_re_u;
	this->t_im_u = t_im_u;

	tile(this->t_re, this->t_im, t_re_u, t_im_u, this->tx, this->ty);
	bandwidthLimit(this->rx, this->ry, this->t_re, this->t_im);	// kirkland makes mistake here in Fig 5.11
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
	vector<vector<float>> P_re(this->px);
	for(auto &Pi : P_re)
		Pi = vector<float>(this->py, 0.);
	auto P_im = P_re;
	
	float c = -pi * relativistic_wavelength(E) * deltaz;
	float phi;


	auto [kx, ky] = reciprocalPoints(this->px, this->py, this->rx, this->ry);

	for(int i = 0; i < this->px; i++)
		for(int j = 0; j < this->py; j++)
		{
			phi = c * (pow(kx[i],2) + pow(ky[j],2));
			// cout << this->rx;
			P_re[i][j] = cos(phi);
			P_im[i][j] = sin(phi);
		}

	bandwidthLimit(this->rx, this->ry, P_re, P_im);
	this->P_re = P_re;
	this->P_im = P_im;

}