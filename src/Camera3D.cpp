//
// Created by adam on 2/23/21.
//

#include "Camera3D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>


using namespace Afeb;

Camera3D::Camera3D() : _position(0.0f, 0.0f, 1.0f),
                       _fieldOfView(50.0f),
                       _nearPlane(0.01f),
                       _farPlane(100.0f),
                       _viewportAspectRatio(4.0f / 3.0f),
                       _front(0.0f, 0.0f, -1.0f),
                       _right(1.0f, 0.0f, 0.0f),
                       _up(0.0f, 1.0f, 0.0f),
                       _worldUp(_up) {}

// position
const glm::vec3& Camera3D::getPosition() const {
    return _position;
}

void Camera3D::setPosition(const glm::vec3& position) {
    _position = position;
}

void Camera3D::offsetPosition(const glm::vec3& offset) {
    _position += offset;
}

// aspect ratio
void Camera3D::setViewportAspectRatio(float viewportAspectRatio) {
    assert(viewportAspectRatio > 0.0);
    _viewportAspectRatio = viewportAspectRatio;
}

// movement
glm::vec3 Camera3D::forward() const {
    glm::vec3 forward = _front;
    return forward;
}

glm::vec3 Camera3D::right() const {
    glm::vec3 right = _right;
    return right;
}

glm::vec3 Camera3D::up() const {
    glm::vec3 up = _up;
    return up;
}

// matrix
glm::mat4 Camera3D::matrix() const {
    return projection() * glm::lookAt(_position, _position + _front, _up);
}

glm::mat4 Camera3D::projection() const {
    return glm::perspective(glm::radians(_fieldOfView), _viewportAspectRatio, _nearPlane, _farPlane);
}

// input
void Camera3D::processMouseMovement(float xOffset, float yOffset) {
    xOffset *= _mouseSensitivity;
    yOffset *= _mouseSensitivity;
    _yaw += xOffset;
    _pitch += yOffset;

    if (_pitch > 89.0f) {
        _pitch = 89.0f;
    }
    if (_pitch < -89.0f) {
        _pitch = -89.0f;
    }
    updateCameraVectors();
}

void Camera3D::processWheelMovement(int direction) {
    if (direction < 0) {
        _fieldOfView += _zoom;
    } else {
        _fieldOfView -= _zoom;
    }
}

void Camera3D::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);
    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}
