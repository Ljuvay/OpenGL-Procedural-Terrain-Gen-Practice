#include <glad/glad.h>
#include <glfw3.h>
#include <glm-1.0.2/glm/glm.hpp>
#include <glm-1.0.2/glm/gtc/matrix_transform.hpp>
#include <glm-1.0.2/glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Inputs.h"
#include "shader.h"
#include "terrain.h"
#include "Noise.h"
#include "Chunk.h"
#include "window.h"
#include "camera.h"



Perlin terrPerlin;

Terrain::Terrain() {
	seedX = static_cast<double>(rand()) / RAND_MAX * 1000;
	seedY = static_cast<double>(rand()) / RAND_MAX * 1000;
}

void Terrain::generateTerrain(int width, int depth) {

	double scale = 0.0020;
	int octaves = 6;
	double persistence = 0.45;
	//double maxHeight = 500.0;

	

	for (int i = -1 * width; i < width; i++) {
		for (int j = -1 * depth; j < depth; j++) {
			double noiseVal = terrPerlin.OctavePerlin(
				(i + seedX) * scale,
				(j + seedY) * scale,
				0.0, octaves, persistence);

			glm::vec2 pos = { static_cast<float>(i), static_cast<float>(j) };

			auto key = std::pair<int, int>(i, j);
			ChunkDict[key] = new Chunk(pos, static_cast<double>(seedX), static_cast<double>(seedY), terrPerlin);


		}
	}
}

void Terrain::generateChunks(glm::vec3 camPos, Shader& shader) {

	int camChunkX = static_cast<int>(floor(camPos.x / chunkWidth));
	int camChunkZ = static_cast<int>(floor(camPos.z / chunkWidth));

	// Generate new chunks around camera if they don't exist
	for (int i = camChunkX - chunkRenderDistance; i <= camChunkX + chunkRenderDistance; i++) {
		for (int j = camChunkZ - chunkRenderDistance; j <= camChunkZ + chunkRenderDistance; j++) {
			auto key = std::pair<int, int>(i, j);

			// If chunk doesn't exist, create it
			if (ChunkDict.find(key) == ChunkDict.end()) {
				glm::vec2 pos = { static_cast<float>(i), static_cast<float>(j) };
				ChunkDict[key] = new Chunk(pos, seedX, seedY, terrPerlin);

			}
		}
	}

	for (auto& entry : ChunkDict) {

		auto coord = entry.first;
		Chunk* currChunk = entry.second;

		int chunkWorldX = coord.first * chunkWidth;
		int chunkWorldZ = coord.second * chunkWidth;

		if (abs(chunkWorldX - camPos.x) < chunkRenderDistance * chunkWidth &&
			abs(chunkWorldZ - camPos.z) < chunkRenderDistance * chunkWidth)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(chunkWorldX, 0.0f, chunkWorldZ));
			shader.setMat4("model", model);
			currChunk->draw(model);
		}
	}
}

