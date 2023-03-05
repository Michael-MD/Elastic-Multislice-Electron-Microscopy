#include "constants.h"
#include <iostream>
#include "specimen_structure.h"
#include "general_purpose_utils.h"
using namespace std;

int main()
{
	// cout << hc;

	SpecimenStructure l(10,10,400,400);
	auto x = l.scatteringFactor(6,100.,100.);
	writeToFile("6.txt", x);

	x = l.scatteringFactor(14,100.,100.);
	writeToFile("14.txt", x);

	x = l.scatteringFactor(29,100.,100.);
	writeToFile("29.txt", x);

	x = l.scatteringFactor(79,100.,100.);
	writeToFile("79.txt", x);

	x = l.scatteringFactor(92,100.,100.);
	writeToFile("92.txt", x);
	return 0;
}