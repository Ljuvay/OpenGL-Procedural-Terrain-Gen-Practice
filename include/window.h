#ifndef WINDOW_H
#define WINDOW_H


#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include "Inputs.h"
#include "shader.h"
#include "settings.h"

class Window
{
private:
	int width = SCR_WIDTH; 
	int height = SCR_HEIGHT;
	GLFWwindow* window;

public:
	Window();
	~Window();
	void createWindow();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

};

#endif WINDOW_H
