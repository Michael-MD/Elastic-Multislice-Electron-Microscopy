#ifndef _H_LAYER
#define _H_LAYER 1

#include <string>
#include "crystal.h"
#include <vector>
#include "atom.h"
using namespace std;

class layer
{
public:
	layer(float E, int px_u, int py_u, float rx_u, float ry_u, float deltaz) 
	{
		this->E = E;
		this->px_u = px_u;
		this->py_u = py_u;
		this->rx_u = rx_u;
		this->ry_u = ry_u;
		this->deltaz = deltaz;
	};

	void calcTransmissionFunction();
	void calcFreeSpacePropagator();

public:
	float E;
	vector<Atom> atoms;
	int px_u, py_u;							// unitcell grid pixel dimensions
	float rx_u, ry_u;
	float deltaz;							// slice thickness
	vector<vector<float>>	t_re;			// transmission function for each layer
	vector<vector<float>>	t_im;			// transmission function for each layer
	vector<vector<float>>	P_re, P_im;		// free-space propagator for each layer
};


#endif