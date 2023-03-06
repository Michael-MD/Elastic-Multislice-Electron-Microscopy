#include "multislice.h"
#include "crystal.h"
#include "fourier_utils.h"
#include "constants.h"
#include "fft.h"
#include "relativistic_corrections.h"
#include <math.h>
#include <string>
#include <fstream>
#include <tuple>

#include <iostream>
using namespace std;

multislice::multislice(float E, int px, int py, int tx, int ty, int tz, string filename)
{
	/*
	E: beam energy
	(px, py): number of samples in each direction
	(tx, ty, tz): tiling of supercell
	filename: name of .xyz file of crystal
	*/
	
	this->E = E;

	this->px = px;
	this->py = py;

	this->tx = tx;
	this->ty = ty;
	this->tz = tz;

	// currently assumes all atoms on single layer
	crystal c(px, py, filename);
	this->rx_u = c.x();
	this->ry_u = c.y();
	this->rx = c.x() * this->tx;
	this->ry = c.y() * this->ty;


	vector<Atom> layer;
	for(auto atom : c.atoms)
		layer.push_back(atom);
	layers.push_back(layer);
}

void multislice::calcTransmissionFunction()
{
	/*
	Calculate transmission functions for each layer and store in t_re and t_im members.
	The result has been bandwidth limited appropriately.
	*/
	
	// create empty matrix structure
	vector<vector<float>> t_re(this->px);
	for(auto &ti : t_re)
		ti = vector<float>(this->py, 0.);
	vector<vector<float>> t_im = t_re;
	
	// add up structure factors and assumes single layer
	for(auto layer : this->layers)
		for(auto atom : layer)
		{
			auto [F_re, F_im] = atom.structureFactor();
			addMatrix(t_re, t_im, F_re, F_im);
		}

	bandwidthLimit(this->rx_u, this->ry_u, t_re, t_im, true); // bandwidth limit v according to Kirkland
	rad2FFT2(t_re, t_im); // inverse fourier transform result, forward done to match kirkland's convention

	// multiply by constants to sigma * v
	float gamma = relativistic_mass(this->E) / me;
	float lambda = relativistic_wavelength(this->E);
	float prefac = lambda * gamma / (this->rx_u * this->ry_u);
	float tmp;
	for(long unsigned i = 0; i < t_re.size(); i++)
		for(long unsigned j = 0; j < t_re[0].size(); j++)
		{
			tmp = prefac * t_re[i][j];
			t_re[i][j] = cos(tmp);
			t_im[i][j] = sin(tmp);
		}

	bandwidthLimit(this->rx_u, this->ry_u, t_re, t_im);

	this->t_re.push_back(t_re);
	this->t_im.push_back(t_im);
}






