#ifndef _H_FOURIER_UNTILS
#define _H_FOURIER_UNTILS 1

#include <tuple>

/*
useful functions for doing various tasks to do with reciprical space and matrix manipulations.
*/

std::tuple<float*, float*> reciprocalPoints(int px, int py, float rx, float ry);
void bandwidthLimit(int px, int py, float rx, float ry, float **F_re, float **F_im, float *kx, float *ky, float lim = .66);

void handamardProduct(float **A_re, float **A_im, float **B_re, float **B_im, int Nx, int Ny);

#endif