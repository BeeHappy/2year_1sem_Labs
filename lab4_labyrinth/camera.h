#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 200.0f;
const float SENSITIVTY = 0.25f;
const float ZOOM = glm::radians(45.0f);
const  glm::vec3 def_pos = glm::vec3(0.0f, 0.0f, 0.0f);
const  glm::vec3 def_up = glm::vec3(0.0f, 1.0f, 0.0f);

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
    glm::vec3 position;
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw = YAW;
    GLfloat pitch = PITCH;

    GLfloat movementSpeed = SPEED;
    GLfloat mouseSensitivity = SENSITIVTY;
    GLfloat zoom = ZOOM;
    void updateCameraVectors();
public:
    Camera();
    explicit Camera(glm::vec3 = def_pos, glm::vec3 = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat = YAW, GLfloat = PITCH);
    Camera(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
    void mouseScroll(GLfloat);
    void mouseMovement(GLfloat, GLfloat, GLboolean = true);
    glm::mat4 getViewMatrix() const;
    void keyboard(Camera_Movement, GLfloat);
    GLfloat getZoom() const;
    ~Camera();
};
