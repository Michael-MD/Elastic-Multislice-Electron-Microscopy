#ifndef _H_MULTISLICE
#define _H_MULTISLICE 1

#include <string>
#include "crystal.h"
#include <vector>
#include "atom.h"
#include "layer.h"
using namespace std;

class multislice
{
	/*
	handles main components of multislice. These being storing the wave function, crystal and 
	methods to propogate wave function and calculating image intensity.
	*/
public:
	multislice(float E, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s);
	virtual void calcPsi0() = 0;
	void propagateWaveFunctionThroughCrystal();
	void calcLensTF(float Cs, float deltaf, float alpha_max);
	float intensity();

public:
	int tx, ty, tz;					// unitcell tiling
	int px_u, py_u, px, py;					// unitcell grid pixel dimensions
	float rx_u, ry_u, rx, ry;		// total real space dimensions and of unit cell
	float E;
	vector<layer> layers;	// contains vector of atoms in each layer of crystal
	vector<vector<float>> psi_re, psi_im; // wave function
	vector<vector<float>> H0_re, H0_im; // Lens TF
};

#endif