/*
 * This project was completed as a way to introduce myself to OpenGL.
 * Various errors and coding inconsistencies are likely, as I'm new to
 * computer science and OpenGL as a whole.
 *
 * Sources:
 * - LearnOpenGL (https://learnopengl.com)
 * - https://gist.github.com/Flafla2/f0260a861be0ebdeef76
 * - https://github.com/SRombauts/SimplexNoise/blob/master/src/SimplexNoise.cpp
 *
 * Additional help from AI tools for learning and debugging:
 * - OpenAI ChatGPT
 * - Microsoft Copilot
 */


// ---------- Includes ----------
#include <glad/glad.h>
#include <glfw3.h>
#include <glm-1.0.2/glm/glm.hpp>
#include <glm-1.0.2/glm/gtc/matrix_transform.hpp>
#include <glm-1.0.2/glm/gtc/type_ptr.hpp>
#include <iostream>
#include <ctime>
#include "Inputs.h"
#include "shader.h"
#include "window.h"
#include "terrain.h"
using namespace std;



int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	Window* ourWindow = new Window();
	ourWindow->createWindow();

	//clean-up
	glfwTerminate();
	return 0;
}



