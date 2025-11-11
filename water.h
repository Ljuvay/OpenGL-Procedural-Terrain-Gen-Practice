#ifndef WATER_H
#define WATER_H

#include <glad/glad.h>
#include <glfw3.h>

#include <vector>
#include <cmath>

#include "shader.h"
#include "terrain.h"
#include "Noise.h"

class Water
{
public:
	void createWater();
	void createWater(std::vector<float> location);

	void setIndCount(unsigned int i);
	void setVerts(std::vector<float> verticesIn);
	std::vector<float> getVerts();
	void setInds(std::vector<unsigned int> indicesIn);
	std::vector<unsigned int> getInds();
	void WaterColor(float y, double maxH, std::vector<float>& verts);

	void draw() const;
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int indicesCount;
	unsigned int VAO, VBO, EBO;
};



#endif
