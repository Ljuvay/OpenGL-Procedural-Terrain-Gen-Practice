#include "objExporter.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

void objExporter::outputObj(Terrain currTerrain, string file) {
	ofstream myfile(file);

	int count = 0;
	int stride = 6;

	if (myfile.is_open()) {
		cout << "file is open" << endl;
	}

	int offset = 0;

	for (Chunk& chunk : currTerrain.chunks) {
		std::vector<float> currVerts = chunk.getVerts();
		//myfile << "o Chunk" << count << endl;
		for (size_t i = 0; i < currVerts.size(); i += stride) {
			//cout << fixed << setprecision(6) << "v " << currVerts.at(i) << " " << currVerts.at(i + 1) << " " << currVerts.at(i + 2) << endl;
			myfile << fixed << setprecision(6) << "v " << currVerts.at(i) << " " << currVerts.at(i + 1) << " " << currVerts.at(i + 2) << endl;
		}
		offset += currVerts.size() / stride;
		count++;
	}
	count = 0;
	offset = 0;

	for (Chunk& chunk : currTerrain.chunks) {
		std::vector<unsigned int> currInds = chunk.getInds();
		std::vector<float> currVerts = chunk.getVerts();
		for (size_t i = 0; i < currInds.size(); i += 3) {
			myfile << "f " << currInds.at(i) + 1 + offset << " " << currInds.at(i + 1) + 1 + offset << " " << currInds.at(i + 2) + 1 + offset << endl;
		}
		count++;
		offset += currVerts.size() / stride;
	}
}