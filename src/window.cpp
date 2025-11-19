#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <glm-1.0.2/glm/glm.hpp>
#include <glm-1.0.2/glm/gtc/matrix_transform.hpp>
#include <glm-1.0.2/glm/gtc/type_ptr.hpp>
#include "Inputs.h"
#include "shader.h"
#include "window.h"
#include "terrain.h"
#include "camera.h"
#include "water.h"
#include "objExporter.h"

using namespace std;

Camera camera(glm::vec3(100.0f, 400.0f, 250.0f));

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static float lastX = 400.0f;
    static float lastY = 300.0f;
    static bool firstMouse = true;

    if (firstMouse) {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos; // reversed

    lastX = (float)xpos;
    lastY = (float)ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

Window::Window() : window(nullptr) {}
Window::~Window() { glfwDestroyWindow(window); }

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, width, height);
}

void Window::createWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "Test Proc Gen", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Window creation failed\n";
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Chunk ourChunk;
    Shader ourShader("shaders/vertex.glsl", "shaders/fragment.glsl");
    Shader waterShader("shaders/waterVert.glsl", "shaders/waterFrag.glsl");
    Terrain ourTerrain;
    Water ourWater;

    std::vector<float> tempWater;
    tempWater.push_back(5);

    objExporter ourExporter;

    ourWater.createWater(tempWater);
    ourTerrain.generateTerrain(5, 5);
    //Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

    glViewport(0, 0, 800, 600);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        /*
        if (static_cast<int>(deltaTime) % 100000 == 0) {
            cout << "Camera Position" << endl;
            cout << camera.Position.x << " " << camera.Position.y << " " << camera.Position.z << endl;
        }
        */

        userGetInputs(window);

        glClearColor(0.412f, 0.847f, 1.000f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, renderDistance);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        ourShader.setMat4("model", model);


        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        for (const Chunk& chunk : ourTerrain.chunks) {
            chunk.draw();

        }

        glm::mat4 waterModel = glm::mat4(1.0f);
        waterShader.use();
        waterShader.setMat4("view", camera.GetViewMatrix());
        waterShader.setMat4("projection", projection);
        waterShader.setMat4("model", waterModel);
        waterShader.setFloat("u_time", glfwGetTime());
        ourWater.draw();

        
        

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
            ourExporter.outputObj(ourTerrain, "output.obj");
            
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}