#include "Inputs.h"
#include "settings.h"
#include "camera.h"

extern Camera camera;

void userGetInputs(GLFWwindow* window)
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

    
 

      

        

}