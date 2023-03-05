#ifndef _H_FOURIER_UNTILS
#define _H_FOURIER_UNTILS 1

#include <tuple>
#include <vector>
using namespace std;

/*
useful functions for doing various tasks to do with reciprical space and matrix manipulations.
*/

std::tuple<float*, float*> reciprocalPoints(int px, int py, float rx, float ry);
void bandwidthLimit(float rx, float ry, vector<vector<float>> &F_re, vector<vector<float>> &F_im, float lim = .66);

void handamardProduct(vector<vector<float>> &A_re, vector<vector<float>> &A_im, vector<vector<float>> &B_re, vector<vector<float>> &B_im);

#endif