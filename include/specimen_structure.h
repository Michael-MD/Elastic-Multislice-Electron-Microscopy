#ifndef _SPECIMEN_STRUCTURE
#define _SPECIMEN_STRUCTURE 1

#include <vector>
#include <complex>
#include <tuple>
using namespace std;

class SpecimenStructure
{
	/*
	data structure for storing crystal atomic structure and potential information assuming 
	an orthorhombic system.
	*/
public:
	// SpecimenStructure();
	SpecimenStructure(int tx, int ty, int px, int py)
	{
		this->tx = tx;
		this->ty = ty;

		this->px = px;
		this->py = py;
	}	
	
	vector<vector<float>> scatteringFactor(int Z, float rx, float ry);
	tuple<vector<vector<float>>,vector<vector<float>>> structureFactor(int Z, float xf, float yf, float rx, float ry);
	vector<vector<float>> V(int Z, float rx, float ry);

public:
	int tx, ty;	// tiling in x and y directions
	int px, py; // grid size in pixels
	int Z = 6;
};


#endif