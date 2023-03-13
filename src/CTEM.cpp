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
	vector<vector<float>> psi_re(this->px);
	for(auto &psii : psi_re)
		psii = vector<float>(this->py, 1);
	this->psi_re = psi_re;

	vector<vector<float>> psi_im(this->px);
	for(auto &psii : psi_im)
		psii = vector<float>(this->py, 0);
	this->psi_im = psi_im;
}
