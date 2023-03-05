#ifndef _RAD2_FFT
#define _RAD2_FFT 1

#include <vector>
using namespace std;

// 1D FFT
void rad2FFT(vector<float> &xr, vector<float> &xi);
void irad2FFT(vector<float> &Xr, vector<float> &Xi);

// 2D FFT
void rad2FFT2(vector<vector<float>> &xr, vector<vector<float>> &xi);
void irad2FFT2(vector<vector<float>> &Xr, vector<vector<float>> &Xi);

//fftshift
void fftshift(vector<float> &xr, vector<float> &xi);
void fftshift2(vector<vector<float>> &xr, vector<vector<float>> &xi);

#endif