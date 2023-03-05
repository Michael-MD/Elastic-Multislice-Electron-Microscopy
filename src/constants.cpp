#include "constants.h"
#include <complex>

extern const std::complex<double> i1(0, 1);				// complex i
extern const float pi 	= 3.14159265359;
extern const float pi2 	= 2 * 3.14159265359;			// 2pi
extern const float h 	= 6.62607004e-14; 				// plank constant [kg-angstrom^2/s]
extern const float hbar = h / (2 * pi); 				// plank constant [kg-angstrom^2/s]
extern const float c 	= 299792458; 					// speed of light [m/s]
extern const float me 	= 9.10938356e-31; 				// electron mass [kg]
extern const float qe 	= 1.60217662e-19; 				// electron charge [coulomb]
extern const float qeA 	= 1.60217662e1; 				// electron charge [kg-angstrom^2/(s^2-V)]
extern const float R 	= 13.605693122994; 				// rydberg const. [eV]
extern const float a0 	= 0.529177; 					// bohr radius [angstrom]
extern const float eV2J	= 1.60218e-19;					// eV to Joules conversion
extern const float m0c2	= me * c*c / eV2J;				// rest mass energy of electron [eV]
extern const float hc	= h * c * 1e-10 / eV2J;			// hc = 12398.4 [eV-angstrom]