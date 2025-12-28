#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include "Inputs.h"
#include "shader.h"
#include "terrain.h"
#include "Noise.h"
#include "Chunk.h"

Chunk::Chunk() {
	float vertices[] = {
		//Top

		//Vertices          //Colors
		-0.5f, 0.0f, -0.5f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.5f, 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, // top left
		 0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom right
		 0.5f, 0.0f,  0.5f, 1.0f, 1.0f, 1.0f, // top right

		 //Bottom
		 -0.5f, 1.0f, -0.5f, 1.0f, 1.0f, 1.0f, // bottom left
		 -0.5f, 1.0f,  0.5f, 0.0f, 0.0f, 1.0f, // top left
		  0.5f, 1.0f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
		  0.5f, 1.0f,  0.5f, 1.0f, 0.0f, 0.0f // top right


	};

	unsigned int indices[] = {
		//bottom
		0, 2, 3, //first triangle
		0, 3, 1, // second triangle

		//top
		4, 5, 7,
		4, 7, 6,

		//Front
		1, 3, 5,
		5, 3, 7,

		//Back
		0, 4, 2,
		2, 4, 6,

		//Left
		0, 1, 4,
		4, 1, 5,

		//Right
		2, 6, 3,
		3, 6, 7
	};

	setIndCount(sizeof(indices) / sizeof(unsigned int));

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// Define how vertex data is interpreted by the shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

Chunk::Chunk(glm::vec2 loc, float seedX, float seedY, Perlin& perlin) {

	cX = static_cast<int>(loc[0]); cY = static_cast<int>(loc[1]);

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	double scale = 0.0020;
	int octaves = 6;
	double persistence = 0.45;
	double maxHeight = 500.0;
	//double seedX = static_cast<double>(rand()) / RAND_MAX * 1000;
	//double seedY = static_cast<double>(rand()) / RAND_MAX * 1000;

	for (int i = 0; i <= chunkWidth; i++) {
		for (int j = 0; j <= chunkWidth; j++) {

			float worldX = static_cast<float>(i) + (loc[0] * chunkWidth);
			float worldZ = static_cast<float>(j) + (loc[1] * chunkWidth);

			// Apply scale and seed BEFORE passing to perlin
			float noiseX = (worldX + seedX) * scale;
			float noiseZ = (worldZ + seedY) * scale;

			float noiseVal = static_cast<float>(perlin.OctavePerlin(
				noiseX,
				noiseZ,
				0.0f,
				octaves,
				persistence
			));

			float y = static_cast<float>(noiseVal * maxHeight);

			vertices.push_back(static_cast<float>(i));    // x position
			vertices.push_back(y);                        // y position
			vertices.push_back(static_cast<float>(j));    // z position

			//TerrColor(y, maxHeight, vertices);
			vertices.push_back(0.0f);
			vertices.push_back(0.0f);
			vertices.push_back(0.0f);

			

		}
	}

	for (int i = 0; i < chunkWidth; ++i) {
		for (int j = 0; j < chunkWidth; ++j) {
			int increment = static_cast<int>(chunkWidth) + 1;
			int topLeft = static_cast<int>(i) * increment + static_cast<int>(j);
			int topRight = topLeft + 1;
			int bottomLeft = (static_cast<int>(i) + 1) * increment + static_cast<int>(j);
			int bottomRight = bottomLeft + 1;

			// Triangle 1 (flipped)
			indices.push_back(topLeft);
			indices.push_back(topRight);
			indices.push_back(bottomLeft);

			// Triangle 2 (flipped)
			indices.push_back(topRight);
			indices.push_back(bottomRight);
			indices.push_back(bottomLeft);
			
		}
	}

	this->vertices = vertices;
	this->indices = indices;

	setIndCount(static_cast<int>(indices.size()));

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// Define how vertex data is interpreted by the shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	

	glBindVertexArray(0);
}

Chunk::Chunk(Chunk&& other) noexcept
{
	vertices = std::move(other.vertices);
	indices = std::move(other.indices);
	indicesCount = other.indicesCount;

	VAO = other.VAO;
	VBO = other.VBO;
	EBO = other.EBO;

	cX = other.cX;
	cY = other.cY;

	other.VAO = 0;
	other.VBO = 0;
	other.EBO = 0;
}

Chunk& Chunk::operator=(Chunk&& other) noexcept
{
	if (this != &other)
	{
		vertices = std::move(other.vertices);
		indices = std::move(other.indices);
		indicesCount = other.indicesCount;

		VAO = other.VAO;
		VBO = other.VBO;
		EBO = other.EBO;

		cX = other.cX;
		cY = other.cY;

		other.VAO = 0;
		other.VBO = 0;
		other.EBO = 0;
	}
	return *this;
}


// No longer in use, color is decided in shader
void Chunk::TerrColor(float y, double H, std::vector<float>& verts) {
	double Hscale = y / H;

	/*if (Hscale <= 0.425) {
		// Water
		verts.push_back(0.000f); verts.push_back(0.200f); verts.push_back(0.600f);
	}*/

	if (Hscale <= 0.45) {
		// Sand
		verts.push_back(0.761f); verts.push_back(0.698f); verts.push_back(0.502f);
	}
	else if (Hscale <= 0.50) {
		// Grass
		verts.push_back(0.124f); verts.push_back(0.252f); verts.push_back(0.000f);
	}
	else if (Hscale <= 0.60) {
		// Rock
		verts.push_back(0.500f); verts.push_back(0.500f); verts.push_back(0.500f);
	}
	else {
		// Snow
		verts.push_back(1.000f); verts.push_back(1.000f); verts.push_back(1.000f);
	}
} 

void Chunk::draw(const glm::mat4& model) const {
	glBindVertexArray(VAO);
	//cout << indicesCount;
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	//cout << "drawing chunks";
}

unsigned int Chunk::getIndCount() {
	return indicesCount;
}

void Chunk::setIndCount(unsigned int i) {
	indicesCount = i;
}

std::vector<float> Chunk::getVerts() {
	return vertices;
}

std::vector<unsigned int> Chunk::getInds() {
	return indices;
}