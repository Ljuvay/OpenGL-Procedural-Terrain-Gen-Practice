#ifndef TERRAIN_H
#define TERRAIN_H

#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include "Inputs.h"
#include "shader.h"

class Chunk
{
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int indicesCount;
	unsigned int VAO, VBO, EBO;
public:
	Chunk();
	Chunk(vector<float> location, double seedX, double seedY, double& noiseVal);
	void draw() const;
	unsigned int getIndCount();
	void setIndCount(unsigned int i);
	void TerrColor(float y, double maxH, std::vector<float>& verts);
	std::vector<float> getVerts();
	std::vector<unsigned int> getInds();
};

class Terrain
{
private:
	//std::vector<Chunk> chunks;
public:
	std::vector<Chunk> chunks;
	void generateTerrain(int width, int depth);
	void genNorms();
	//void combineChunks();
};

#endif
