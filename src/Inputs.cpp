#include "Inputs.h"
#include "settings.h"
#include "camera.h"
#include "terrain.h"
#include "objExporter.h"
#include "window.h"
#include "Chunk.h"

extern Camera camera;

void userGetInputs(GLFWwindow* window, Terrain terrain, objExporter exporter, float deltaTime)
{
    //float cameraSpeed = static_cast<float>(2.5 * deltaTime);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        glEnable(GL_CULL_FACE);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        glDisable(GL_CULL_FACE);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.CameraSpeed = CAMSPEEDSETTING * 3.0f;
    else
        camera.CameraSpeed = CAMSPEEDSETTING;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessInputs(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessInputs(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessInputs(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessInputs(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessInputs(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.ProcessInputs(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        exporter.outputObj(terrain, "output.obj");

    
 

      

        

}