#include "crystal.h"

#include <string>
#include <vector>
#include <fstream>
using namespace std;

crystal::crystal(int px, int py, string filename)
{
	/*
	Read in crystal structure information from .xyz file. These are assumed to be 
	located in directory "./structures/".
	*/
	ifstream xyzFile("structures/" + filename);
	xyzFile >> crystalname;	// crystal name

	xyzFile >> unitcell[0] 
			>> unitcell[1]
			>> unitcell[2]

			>> ang[0] 
			>> ang[1]
			>> ang[2];

	Atom a;
	while(xyzFile >> a.Z)
	{
		if(a.Z == -1) break;
		xyzFile	>> a.xf
				>> a.yf
				>> a.zf
				>> a.occ
				>> a.msd;
		atoms.push_back(a);
	}

	this->px = px;
	this->py = py;
}