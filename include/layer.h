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
	layer(float E, int px_u, int py_u, float rx_u, float ry_u, int tx, int ty, float deltaz) 
	{
		this->E = E;
		this->px_u = px_u;
		this->py_u = py_u;
		this->rx_u = rx_u;
		this->ry_u = ry_u;
		this->rx = rx * tx;
		this->ry = ry * ty;
		this->tx = tx;
		this->ty = ty;
		this->deltaz = deltaz;
	};

	void calcTransmissionFunction();
	void calcFreeSpacePropagator();

public:
	float E;
	vector<Atom> atoms;
	int px_u, py_u;							// unitcell grid pixel dimensions
	int tx, ty;								// tiling
	float rx_u, ry_u, rx, ry;
	float deltaz;							// slice thickness
	vector<vector<float>> t_re_u, t_im_u, t_re, t_im;	// transmission function for layer
	vector<vector<float>> P_re_u, P_im_u, P_re, P_im;	// free-space propagator for layer

};


#endif