#include "fourier_utils.h"
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <tuple>
#include <vector>
using namespace std;

#define complex_mult(cr, ci, ar, ai, br, bi) { \
	cr = (ar) * (br) - (ai) * (bi);			   \
	ci = (ar) * (bi) + (ai) * (br);			   \
}

std::tuple<float*, float*> reciprocalPoints(int px, int py, float rx, float ry)
{
	/*
	calculates and returns array of reciprical lattice points as
					[0, 1, ...,   n/2-1,     -n/2, ..., -1]fs / (n)   if n is even
    				[0, 1, ..., (n-1)/2, -(n-1)/2, ..., -1]fs / (n)   if n is odd
    where fs is sampling frequency and n is sequence length.
	*/ 
	
	// sampling frequency
	float fs_x = px / rx;
	float fs_y = py / ry;

	float *kx = (float*) malloc(sizeof(float) * px);
	float *ky = (float*) malloc(sizeof(float) * py);

	int n0_x, n0_y, n1_x, n1_y;

	n0_x = (px % 2 == 0) ? px / 2 - 1 : (px - 1) / 2;
	n0_y = (py % 2 == 0) ? py / 2 - 1 : (py - 1) / 2; 

	n1_x = (px % 2 == 0) ? -px / 2 : -(px - 1) / 2;
	n1_y = (py % 2 == 0) ? -py / 2 : -(py - 1) / 2; 

	float cx = fs_x / px, cy = fs_y / py;

	int nx = 0, ny = 0;

	for(int i = 0; i < px; i++)
	{
		if(nx > n0_x) nx = n1_x;
		if(ny > n0_y) ny = n1_y;

		(kx)[i] = (nx++) * cx;
		(ky)[i] = (ny++) * cy;
	}

	return {kx, ky};

}


void bandwidthLimit(float rx, float ry, vector<vector<float>> &F_re, vector<vector<float>> &F_im, float lim)
{
	/*
	bandwidth limits the signal, default is given by 2/3 k_max where k_max is the nyquist frequency.
	*/
	int px = F_re.size(), py = F_re[0].size();
	float kmax = std::min(px / rx, py / ry) / 2; // nyquist frequency
	float klim = lim*kmax;
	
	auto [kx,ky] = reciprocalPoints(px, py, rx, ry);
	float k2;

	for(int i = 0; i < px; i++)
		for(int j = 0; j < py; j++)
		{
			k2 = sqrt(pow(kx[i],2) + pow(ky[j],2));
			if(k2 >= klim)
			{
				F_re[i][j] = 0;
				F_im[i][j] = 0;
			}
		}
}


void handamardProduct(vector<vector<float>> &A_re, vector<vector<float>> &A_im, vector<vector<float>> &B_re, vector<vector<float>> &B_im)
{
	/*
	takes the handamard product of two matrices of the same dimensions and stores the result
	in matrix B.
	Note: To save time, this function doesn't check the dimensions.
	*/
	int px = A_re.size(), py = A_re[0].size();
	for(int i = 0; i < px; i++)
		for(int j = 0; j < py; j++)
		{
			complex_mult(	B_re[i][j], B_im[i][j],
							A_re[i][j], A_im[i][j],
							B_re[i][j], B_im[i][j] );
		}
}