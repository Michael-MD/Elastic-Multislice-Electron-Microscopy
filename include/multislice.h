#ifndef _H_MULTISLICE
#define _H_MULTISLICE 1

#include <string>
#include "crystal.h"

using namespace std;

class multislice
{
	/*
	handles main components of multislice. These being storing the wave function, crystal and 
	methods to propogate wave function and calculating image intensity.
	*/
public:
	multislice(float E, int px, int py, int tx, int ty, int tz, string filename);

public:
	int tx, ty, tz;	// unitcell tiling
	int px, py;	// grid pixel dimensions
	float rx, ry;
	float E;
};

#endif