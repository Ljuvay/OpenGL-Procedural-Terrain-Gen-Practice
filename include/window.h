#ifndef WINDOW_H
#define WINDOW_H


#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include "Inputs.h"
#include "shader.h"
#include "settings.h"
#include "terrain.h"
#include "objExporter.h"
#include "water.h"
#include "Chunk.h"

class Window
{
private:
	int width = SCR_WIDTH; 
	int height = SCR_HEIGHT;
	GLFWwindow* window = nullptr;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
	Window();
	~Window();

	void createWindow();
	void run(Terrain& terrain, Water& water, Shader& terrainShader, Shader& waterShader, objExporter& exporter); // render loop

};

#endif
