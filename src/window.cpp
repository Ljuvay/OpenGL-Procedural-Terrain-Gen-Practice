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

    glViewport(0, 0, 800, 600);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::run(Terrain& terrain, Water& water, Shader& terrainShader, Shader& waterShader, objExporter& exporter) {
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        userGetInputs(window, terrain, exporter, deltaTime);

        glClearColor(0.412f, 0.847f, 1.000f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, renderDistance);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);

        terrainShader.use();
        terrainShader.setMat4("model", model);
        terrainShader.setMat4("projection", projection);
        terrainShader.setMat4("view", view);
        glUniform1f(
            glGetUniformLocation(terrainShader.ID, "maxHeight"),
            500.0f
        );

        terrain.generateChunks(camera.Position, terrainShader);

        glm::mat4 waterModel = glm::mat4(1.0f);
        waterShader.use();
        waterShader.setMat4("view", camera.GetViewMatrix());
        waterShader.setMat4("projection", projection);
        waterShader.setMat4("model", waterModel);
        waterShader.setFloat("u_time", static_cast<float>(glfwGetTime()));
        water.draw();

        
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}