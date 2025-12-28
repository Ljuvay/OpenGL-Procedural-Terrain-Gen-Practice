#ifndef CHUNK_H
#define CHUNK_H

#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>

#include "Noise.h"

class Chunk
{
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> cCords;
	unsigned int indicesCount;
	unsigned int VAO, VBO, EBO;
	int cX, cY;

public:
	Chunk();
	Chunk(glm::vec2 loc, float seedX, float seedY, Perlin& perlin);

	Chunk(const Chunk&) = delete;
	Chunk& operator=(const Chunk&) = delete;

	Chunk(Chunk&& other) noexcept;
	Chunk& operator=(Chunk&& other) noexcept;


	void draw(const glm::mat4& model) const;
	unsigned int getIndCount();
	void setIndCount(unsigned int i);
	void TerrColor(float y, double maxH, std::vector<float>& verts);
	std::vector<float> getVerts();
	std::vector<unsigned int> getInds();
	int getcX() {
		return cX;
	}
	int getcY() {
		return cY;
	}
};





#endif