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