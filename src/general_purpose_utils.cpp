#include "general_purpose_utils.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;


void writeToFile(string filename, vector<vector<float>> &x)
{
	ofstream intensityFile(filename);
	for(long unsigned int i = 0; i < x.size(); i++)
	{
		for(long unsigned int j = 0; j < x[0].size(); j++)
			intensityFile << x[i][j] << '\t';
		
		intensityFile << '\n';
	}

	intensityFile.close();
}

void tile(vector<vector<float>> &C_re, vector<vector<float>> &C_im, vector<vector<float>> &B_re, vector<vector<float>> &B_im, int tx, int ty)
{
	/*
	Tiles out B onto A, the tiling will begin from the top left corner. The number of repeats
	along each dimension is given by tx, ty.
	*/
	vector<vector<float>> A_re(tx * B_re.size());
	for(auto &A_rei : A_re)
		A_rei = vector<float>(ty * B_re[0].size());
	auto A_im = A_re;

	float a, b;
	for(unsigned long i = 0; i < A_re.size(); i++)
		for(unsigned long j = 0; j < A_re[0].size(); j++)
		{
			a = i % B_re.size();
			b = j % B_im.size();
			A_re[i][j] = B_re[a][b];
			A_im[i][j] = B_im[a][b];
		}

	C_re = A_re;
	C_im = A_im;
}