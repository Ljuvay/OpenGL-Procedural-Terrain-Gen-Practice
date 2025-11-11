/*
* Camera.h and Camera.cpp are based off of the LearnOpenGL textbook
*/

#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <chrono>
#include <glm-1.0.2/glm/glm.hpp>
#include <glm-1.0.2/glm/gtc/matrix_transform.hpp>
#include <glm-1.0.2/glm/gtc/type_ptr.hpp>
#include "Inputs.h"
#include "camera.h"
#include "settings.h"
#include "shader.h"


// Constructor with glm::vec3
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Position(position), WorldUp(up), yaw(yaw), pitch(pitch),
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), CameraSpeed(SPEED),
    MouseSens(SENSITIVITY)
{
    updateCameraVectors();
}

// Returns the view matrix using LookAt
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

// Processes keyboard input
void Camera::ProcessInputs(Camera_Movement direction, float deltaTime)
{
    float velocity = CameraSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
    if (direction == UP)
        Position += Up * velocity;
    if (direction == DOWN)
        Position -= Up * velocity;
}

// Processes mouse movement
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSens;
    yoffset *= MouseSens;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}

// Updates Front, Right, and Up vectors from yaw and pitch
void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

