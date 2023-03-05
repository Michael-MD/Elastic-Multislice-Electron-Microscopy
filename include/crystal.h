#ifndef _CRYSTAL
#define _CRYSTAL 1

#include <string>
#include <vector>
#include "atom.h"

class crystal
{
	/*
	Stores information about atoms in crystal and slicing.
	*/
public:
	crystal() {};
	crystal(int px, int py, std::string filename);

	float x() {return unitcell[0];}
	float y() {return unitcell[1];}
	float z() {return unitcell[2];}

	float alpha() 	{return ang[0];}
	float beta() 	{return ang[1];}
	float gamma() 	{return ang[2];}

public:
	int px, py;
	std::string crystalname;
	std::vector<Atom> atoms;
	float unitcell[3];	// unitcell dimensions in Ang.
	float ang[3]; // basis intersection angles in degrees

private:
};

#endif