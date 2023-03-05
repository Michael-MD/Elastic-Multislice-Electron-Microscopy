#include "fourier_utils.h"
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <tuple>


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