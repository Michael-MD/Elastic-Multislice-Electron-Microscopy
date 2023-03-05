#include "relativistic_corrections.h"
#include "constants.h"
#include <math.h>

float relativistic_mass(float E)
{
	// Takes in energy of electron in eV and returns relativistic mass in kg
	return me * (1 + E / m0c2);	

}

float relativistic_wavelength(float E)
{
	// Takes in energy of electron in eV and returns relativistic de-broglie wavelength in angstroms
	return hc / sqrt(E * (2 * m0c2 + E));
}


