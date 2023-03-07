#include "multislice.h"
#include "crystal.h"
#include "fourier_utils.h"
#include "constants.h"
#include "fft.h"
#include "layer.h"
#include "relativistic_corrections.h"
#include <math.h>
#include <string>
#include <fstream>
#include <tuple>

#include <iostream>
using namespace std;

multislice::multislice(float E, int px_u, int py_u, int tx, int ty, int tz, string filename)
{
	/*
	E: beam energy
	(px, py): number of samples in each direction
	(tx, ty, tz): tiling of supercell
	filename: name of .xyz file of crystal
	*/
	
	this->E = E;

	this->px_u = px_u;
	this->py_u = py_u;
	this->px = px_u * tx;
	this->py = py_u * ty;


	this->tx = tx;
	this->ty = ty;
	this->tz = tz;

	// ****** currently assumes all atoms on single layer ******
	crystal c(this->px_u, this->py_u, filename);
	this->rx_u = c.x();
	this->ry_u = c.y();
	this->rx = c.x() * this->tx;
	this->ry = c.y() * this->ty;

	// arrange atoms in layers, currently all placed in one layer
	layer l(E, px_u, py_u, this->rx_u, this->ry_u, this->tx, this->ty, c.z());
	vector<Atom> atoms;
	for(auto atom : c.atoms)
		atoms.push_back(atom);


	l.atoms = atoms;
	l.calcTransmissionFunction();
	l.calcFreeSpacePropagator();
	layers.push_back(l);



	// ****** initilize with plane wave of unit intensity at each point, currently unnormalized ******
	vector<vector<float>> psi_re(this->px);
	for(auto &psii : psi_re)
		psii = vector<float>(this->py, 1);
	this->psi_re = psi_re;

	vector<vector<float>> psi_im(this->px);
	for(auto &psii : psi_im)
		psii = vector<float>(this->py, 0);
	this->psi_im = psi_im;
}


void multislice::propagateWaveFunctionThroughCrystal()
{
	for(auto layer : layers)
	{
		handamardProduct(this->psi_re, this->psi_im, layer.t_re, layer.t_im);
		irad2FFT2(this->psi_re, this->psi_im);
		handamardProduct(this->psi_re, this->psi_im, layer.P_re, layer.P_im);
		rad2FFT2(this->psi_re, this->psi_im);
	}
}