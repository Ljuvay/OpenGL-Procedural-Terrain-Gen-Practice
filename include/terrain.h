#ifndef TERRAIN_H
#define TERRAIN_H

#include <glad/glad.h>
#include <glfw3.h>
#include <glm-1.0.2/glm/glm.hpp>
#include <glm-1.0.2/glm/gtc/matrix_transform.hpp>
#include <glm-1.0.2/glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

#include "shader.h"
#include "Chunk.h"

// Custom hash function for std::pair<int, int>
struct PairHash {
	std::size_t operator()(const std::pair<int, int>& p) const {
		auto h1 = std::hash<int>{}(p.first);
		auto h2 = std::hash<int>{}(p.second);
		return h1 ^ (h2 << 1);
	}
};

class Terrain
{
private:
	
public:

	float seedX, seedY;

	Terrain();

	std::unordered_map<std::pair<int, int>, Chunk*, PairHash> ChunkDict;
	//std::vector<Chunk> chunks;
	void generateTerrain(int width, int depth);
	void generateChunks(glm::vec3 camPos, Shader& shader);
	void genNorms();
	//void combineChunks();
};

#endif
