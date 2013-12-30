#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

namespace ILEngine {

Camera::Camera(glm::vec3 p, glm::vec3 u) {
    this->setPosition(p);
    this->setUp(u);
}

void Camera::setPosition(glm::vec3 p) {
    this->_position = p;
}

void Camera::setUp(glm::vec3 up) {
    this->_up = up;
}

glm::vec3 Camera::position() {
    return this->_position;
}

glm::vec3 Camera::up() {
    return this->_up;
}

glm::mat4 Camera::lookAt(glm::vec3 p) {
    return glm::lookAt(
        this->_position,
        p,
        this->_up
    );
}

}
