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
	multislice(float E, int px, int py, int tx, int ty, int tz, string filename);
	void propagateWaveFunctionThroughCrystal();

public:
	int tx, ty, tz;					// unitcell tiling
	int px_u, py_u, px, py;					// unitcell grid pixel dimensions
	float rx, ry, rx_u, ry_u;		// total real space dimensions and of unit cell
	float E;
	vector<layer> layers;	// contains vector of atoms in each layer of crystal
	vector<vector<float>> psi_re, psi_im; // wave function
};

#endif