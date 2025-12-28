#ifndef INPUTS_H
#define INPUTS_H

#include <glad/glad.h>
#include <glfw3.h>
#include <glm-1.0.2/glm/glm.hpp>
#include <glm-1.0.2/glm/gtc/matrix_transform.hpp>
#include <glm-1.0.2/glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include "camera.h"
#include "settings.h"
#include "terrain.h"
#include "objExporter.h"
#include "chunk.h"

using namespace std;

void userGetInputs(GLFWwindow* window, Terrain terrain, objExporter exporter, float deltaTime);



#endif INPUTS_H





