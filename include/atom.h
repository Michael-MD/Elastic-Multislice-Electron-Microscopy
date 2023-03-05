#ifndef _SPECIMEN_STRUCTURE
#define _SPECIMEN_STRUCTURE 1

#include <vector>
#include <complex>
#include <tuple>
using namespace std;

class Atom
{
	/*
	data structure for storing atom information such as potential assuming.
	*/
public:
	Atom() {};
	Atom(int Z, float xf, float yf, float zf, int px, int py, float rx, float ry)
	{
		this->Z = Z;

		this->xf = xf;
		this->yf = yf;
		this->zf = zf;

		this->px = px;
		this->py = py;
		this->rx = rx;
		this->ry = ry;

		// calculate and store potential of atom
		this->calcPotenial();
	}
	
	vector<vector<float>> scatteringFactor();
	tuple<vector<vector<float>>,vector<vector<float>>> structureFactor();
	void calcPotenial();

public:
	int px, py, rx, ry; 		// grid size in pixels
	float occ, msd;				// occupancy, mean-square displacement
	float xf, yf, zf; 			// fractional coordinates of atom
	int Z;						// atomic number
	vector<vector<float>> v;	// atom potential
};


#endif