#include "multislice.h"
#include "crystal.h"
#include "fourier_utils.h"
#include "constants.h"
#include "fft.h"
#include "layer.h"
#include "relativistic_corrections.h"
#include "general_purpose_utils.h"
#include <math.h>
#include <string>
#include <fstream>
#include <tuple>

#include <iostream>
using namespace std;

multislice::multislice(float E, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s)
{
	/*
	E: beam energy
	(px, py): number of samples in each direction
	(tx, ty, tz): tiling of supercell
	filename: name of .xyz file of crystal
	*/
	
	this->E = E;

	this->px_u = px / tx;
	this->py_u = py / ty;
	this->px = px;
	this->py = py;


	this->tx = tx;
	this->ty = ty;
	this->tz = tz;

	// ****** currently assumes all atoms on single layer ******
	crystal c(this->px_u, this->py_u, filename);
	this->rx_u = c.x();
	this->ry_u = c.y();
	this->rx = c.x() * this->tx;
	this->ry = c.y() * this->ty;

	/*
							**** create layers ****
	array of slices in fractions of total supercell z-depth. For example,
	splitting sample in thirds is given by s = [.33, .66]. Then each layer is stored
	in an array of AtomicStructure data types.
	*/

	auto lindex = [s](float z)
	{
		/*
		returns index of layer e.g. if s = [.33,.66], then lindex(.2) = 0, lindex(.5) = 1, lindex(.8) = 2.
		Using this scheme the z-coordinate of the unit cell is parallel with the optical axis.
		*/
		int Nl = s.size();
		for (int nl = 0; nl < Nl; nl++)
	      if (z < s[nl]) return nl;
	    return Nl;
	};

	float rz_u = c.z();
	auto th =[s, rz_u] (int i) {
		/*
		returns thinkess of ith slice.
		*/
	    int Nl = s.size();
	    if(i == Nl) return (1 - s[i-1]) * rz_u;
	    else if(i == 0) return s[i] * rz_u;
	    return (s[i] - s[i-1]) * rz_u;
	  };


	// arrange atoms in layers, currently all placed in one layer
	int ns = s.size() + 1;

	vector<layer> layers(ns, layer(E, px_u, py_u, this->rx_u, this->ry_u, this->tx, this->ty, c.z()));
	for(int i = 0; i < ns; i++)
		layers[i].deltaz = th(i);

	int j;
	for(auto atom : c.atoms)
	{
		j = lindex(atom.zf * c.z());
		layers[j].atoms.push_back(atom);
	}

	for(auto &layer : layers)
	{
		layer.calcTransmissionFunction();
		layer.calcFreeSpacePropagator();
	}

	this->layers = layers;


	// initilize wave function
	vector<vector<float>> psi_re(this->px);
	for(auto &psii : psi_re)
		psii = vector<float>(this->py);
	this->psi_re = psi_re;
	this->psi_im = psi_re;
}


void multislice::propagateWaveFunctionThroughCrystal()
{
	for(int i = 0; i < this->tz; i++)
		for(auto layer : layers)
		{
			handamardProduct(this->psi_re, this->psi_im, layer.t_re, layer.t_im);
			irad2FFT2(this->psi_re, this->psi_im);
			handamardProduct(this->psi_re, this->psi_im, layer.P_re, layer.P_im);
			rad2FFT2(this->psi_re, this->psi_im);
		}
}


void multislice::calcLensTF(float Cs, float deltaf, float alpha_max)
{
	/*
	implements objective lens frequency response in back-focal plane. No need for bandwidth
	limiting since this will be multiplied by the wave fucntion which is already bandwidth limited.
	Models defocus and third-order spherical aberration only. Also implements aperature.
	Cs[mm]
	deltaf[Ang]
	alphap_max[mrad]
	*/
	auto [kx, ky] = reciprocalPoints(this->px, this->py, this->rx, this->ry);
	float lambda = relativistic_wavelength(this->E);
	float lambda2 = pow(lambda, 2);

	Cs *= 1e7;
	alpha_max *= 1e-3;

	vector<vector<float>> H0_re(this->px);
	for(auto &H0_rei : H0_re)
		H0_rei = vector<float>(this->py);
	auto H0_im = H0_re;

	double k2, chi;
	for(int i = 0; i < this->px; i++)
		for(int j = 0; j < this->py; j++)
		{
			k2 = pow(kx[i],2) + pow(ky[j],2);
			if(lambda * sqrt(k2) < alpha_max)
			{
				chi = pi * lambda * k2 * (.5 * Cs * lambda2 * k2 - deltaf);
				H0_re[i][j] = cos(chi);
				H0_im[i][j] = -sin(chi);
			}
			else
			{
				H0_re[i][j] = 0;
				H0_im[i][j] = 0;
			}
		}

	this->H0_re = H0_re;
	this->H0_im = H0_im;
}


float multislice::totalIntensity()
{
	/*
	calculates total intensity of psi_re, psi_im
	*/
	float I = 0;
	auto [kx, ky] = reciprocalPoints(this->px, this->py, this->rx, this->ry);
	for(int i = 0; i < this->px; i++)
		for(int j = 0; j < this->py; j++)
			I += (pow(this->psi_re[i][j],2) + pow(this->psi_im[i][j],2)) * this->D(kx[i], ky[j]);
	return I;
}