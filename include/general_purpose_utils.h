#ifndef _GENERAL_PURPOSE_UTILS
#define _GENERAL_PURPOSE_UTILS 1

#include <string>
#include <vector>
using namespace std;

void writeToFile(string filename, vector<vector<float>> &x);
void tile(vector<vector<float>> &C_re, vector<vector<float>> &C_im, vector<vector<float>> &B_re, vector<vector<float>> &B_im, int tx, int ty);

#endif