#include "stdafx.h"
#include "camera.h"
#include <glm/gtc/matrix_transform.inl>

void Camera::updateCameraVectors() {
    glm::vec3 loc_front;
    loc_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    loc_front.y = sin(glm::radians(pitch));
    loc_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    this->front = glm::normalize(loc_front);
    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up    = glm::normalize(glm::cross(this->right, this->front));
}

Camera::Camera() {
    front = glm::vec3(0.0f, 0.0f, -1.0f);
}

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) {
    this->position = position;
    worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) {
    position = glm::vec3(posX, posY, posZ);
    worldUp = glm::vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

void Camera::mouseScroll(GLfloat yoffset) {
    if (zoom >= glm::radians(1.0f) && zoom <= glm::radians(45.0f))
        zoom -= glm::radians(yoffset);
    if (zoom < glm::radians(1.0f))
        zoom = glm::radians(1.0f);
    if (zoom > glm::radians(45.0f))
        zoom = glm::radians(45.0f);
}

void Camera::mouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean limPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (limPitch)	{
        if (this->pitch > 89.0f)
            this->pitch = 89.0f;
        if (this->pitch < -89.0f)
            this->pitch = -89.0f;
    }

    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::keyboard(Camera_Movement direction, GLfloat deltaTime) {
    GLfloat velocity = movementSpeed * deltaTime;

    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;

    //position.y = 0.0f;
}

GLfloat Camera::getZoom() const {
    return zoom;
}

Camera::~Camera() {}
