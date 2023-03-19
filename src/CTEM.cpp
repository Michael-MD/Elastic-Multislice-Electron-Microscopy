#include "CTEM.h"
#include "multislice.h"
#include <vector>
#include <string>
using namespace std;


CTEM::CTEM(float E, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s,
			float Cs, float deltaf, float alpha_max)
	: multislice(E, px, py, tx, ty, tz, filename, s)
{
	this->calcPsi0();
	this->propagateWaveFunctionThroughCrystal();
	this->passThroughObjectiveLens(Cs, deltaf, alpha_max);
};


void CTEM::calcPsi0()
{
	/*
	Creates initial wave function with unity real component and zero imaginary component
	*/
	for(long unsigned i = 0; i < this->psi_re.size(); i++)
		for(long unsigned j = 0; j < this->psi_re[0].size(); j++)
		{
			this->psi_re[i][j] = 1;
			this->psi_im[i][j] = 0;
		}
}
