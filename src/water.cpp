#include <cmath>
#include <vector>
#include "water.h"

Perlin perlinWater;

void Water::createWater() {};

void Water::createWater(std::vector<float> pos) {
	
	std::vector<float> tempVertices;
	std::vector<unsigned int> tempIndices;

	double scale = 0.0020;
	int octaves = 6;
	double persistence = 0.45;
	double maxHeight = 5.0;
	double seedX = static_cast<double>(rand()) / RAND_MAX * 1000;
	double seedY = static_cast<double>(rand()) / RAND_MAX * 1000;

	for (int i = 0; i < chunkWidth; i++) {
		for (int j = 0; j < chunkWidth; j++) {

			double noiseVal = perlinWater.OctavePerlin(((chunkWidth + i) + seedX) * scale, ((chunkWidth + j) + seedY) * scale, glfwGetTime() * 0.1, octaves, persistence);

			float y = static_cast<float>(noiseVal * maxHeight);

			tempVertices.push_back(static_cast<float>(i));    // x position
			tempVertices.push_back(y + (500 * 0.425));                        // y position
			tempVertices.push_back(static_cast<float>(j));    // z position

			WaterColor(y, maxHeight, tempVertices);
		}
	}

	for (int i = 0; i < chunkWidth - 1; ++i) {
		for (int j = 0; j < chunkWidth - 1; ++j) {
			int topLeft = i * chunkWidth + j;
			int topRight = topLeft + 1;
			int bottomLeft = topLeft + chunkWidth;
			int bottomRight = bottomLeft + 1;

			// Triangle 1 (flipped)
			tempIndices.push_back(topLeft);
			tempIndices.push_back(topRight);
			tempIndices.push_back(bottomLeft);

			// Triangle 2 (flipped)
			tempIndices.push_back(topRight);
			tempIndices.push_back(bottomRight);
			tempIndices.push_back(bottomLeft);
		}
	}

	setInds(tempIndices);
	setVerts(tempVertices);

	setIndCount(tempIndices.size());

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, tempVertices.size() * sizeof(float), tempVertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tempIndices.size() * sizeof(unsigned int), tempIndices.data(), GL_STATIC_DRAW);

	// Define how vertex data is interpreted by the shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0);
}

void Water::setVerts(std::vector<float> verticesIn) {
	vertices = verticesIn;
}

std::vector<float> Water::getVerts() {
	return vertices;
}

void Water::setInds(std::vector<unsigned int> indicesIn) {
	indices = indicesIn;
}

std::vector<unsigned int> Water::getInds() {
	return indices;
}

void Water::setIndCount(unsigned int i) {
	indicesCount = i;
}

void Water::WaterColor(float y, double H, std::vector<float>& verts) {
	double Hscale = y / H;

	verts.push_back(0.000f); verts.push_back(0.000f); verts.push_back(0.200f);
}

void Water::draw() const {
	glBindVertexArray(VAO);
	//cout << indicesCount;
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	//cout << "drawing chunks";
}