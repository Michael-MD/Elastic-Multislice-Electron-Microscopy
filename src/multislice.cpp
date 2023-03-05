#include "multislice.h"
#include "crystal.h"
#include "fourier_utils.h"
#include "constants.h"
#include "fft.h"
#include "relativistic_corrections.h"
#include <math.h>
#include <string>
#include <fstream>

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

	crystal c(px, py, filename);


}