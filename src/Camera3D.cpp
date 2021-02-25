//
// Created by adam on 2/23/21.
//

#include "Camera3D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

using namespace Afeb;

// must be less than 90 to avoid gimbal lock
static const float MaxVerticalAngle = 85.0f;

Camera3D::Camera3D() : _position(0.0f, 0.0f, 1.0f),
                       _horizontalAngle(0.0f),
                       _verticalAngle(0.0f),
                       _fieldOfView(15.0f),
                       _nearPlane(0.01f),
                       _farPlane(100.0f),
                       _viewportAspectRatio(4.0f / 3.0f),
                       _front(0.0f, 0.0f, -1.0f),
                       _right(1.0f, 0.0f, 0.0f),
                       _up(0.0f, 1.0f, 0.0f),
                       _worldUp(_up) {}

const glm::vec3& Camera3D::position() const {
    return _position;
}

void Camera3D::setPosition(const glm::vec3& position) {
    _position = position;
}

void Camera3D::offsetPosition(const glm::vec3& offset) {
    _position += offset;
}

float Camera3D::fieldOfView() const {
    return _fieldOfView;
}

void Camera3D::setFieldOfView(float fieldOfView) {
    assert(fieldOfView > 0.0f && fieldOfView < 180.0f);
    _fieldOfView = fieldOfView;
}

float Camera3D::nearPlane() const {
    return _nearPlane;
}

float Camera3D::farPlane() const {
    return _farPlane;
}

void Camera3D::setNearAndFarPlanes(float nearPlane, float farPlane) {
    assert(nearPlane > 0.0f);
    assert(farPlane > nearPlane);
    _nearPlane = nearPlane;
    _farPlane = farPlane;
}

glm::mat4 Camera3D::orientation() const {
    glm::mat4 orientation(1.0f);
    orientation = glm::rotate(orientation, glm::radians(_verticalAngle), glm::vec3(1, 0, 0));
    orientation = glm::rotate(orientation, glm::radians(_horizontalAngle), glm::vec3(0, 1, 0));
    // std::cout << "orientation: " << glm::to_string(orientation) << std::endl;
    return orientation;
}

void Camera3D::offsetOrientation(float upAngle, float rightAngle) {
    std::cout << "olf horizontal: " << _horizontalAngle << std::endl;
    _horizontalAngle += rightAngle;
    std::cout << "new horizontal: " << _horizontalAngle << std::endl;
    _verticalAngle += upAngle;
    normalizeAngles();
}

void Camera3D::lookAt(glm::vec3 position) {
    assert(position != _position);
    glm::vec3 direction = glm::normalize(position - _position);
    _verticalAngle = glm::radians(asinf(-direction.y));
    _horizontalAngle = -glm::radians(atan2f(-direction.x, -direction.z));
    normalizeAngles();
}

float Camera3D::viewportAspectRatio() const {
    return _viewportAspectRatio;
}

void Camera3D::setViewportAspectRatio(float viewportAspectRatio) {
    assert(viewportAspectRatio > 0.0);
    _viewportAspectRatio = viewportAspectRatio;
}

glm::vec3 Camera3D::forward() const {
    //glm::vec4 forward = glm::inverse(orientation()) * glm::vec4(0, 0, -1, 1);
    // std::cout << "forward: " << glm::to_string(forward) << std::endl;
    glm::vec3 forward = _mouseSensitivity * _front;
    return forward;
}

glm::vec3 Camera3D::right() const {
    glm::vec3 right = _mouseSensitivity * _right;
    return right;
}

glm::vec3 Camera3D::up() const {
    glm::vec3 up = _mouseSensitivity * _up;
    return up;
}

glm::mat4 Camera3D::matrix() const {
    return projection() * glm::lookAt(_position, _position + _front, _up);
}

glm::mat4 Camera3D::projection() const {
    return glm::perspective(glm::radians(_fieldOfView), _viewportAspectRatio, _nearPlane, _farPlane);
}

/*
glm::mat4 Camera3D::view() const {
    return orientation() * glm::translate(glm::mat4(), -_position);
}
 */

void Camera3D::normalizeAngles() {
    _horizontalAngle = fmodf(_horizontalAngle, 360.0f);
    if (_horizontalAngle < 0.0f) {
        _horizontalAngle += 360.0f;
    }
    if (_verticalAngle > MaxVerticalAngle) {
        _verticalAngle = MaxVerticalAngle;
    } else if (_verticalAngle < -MaxVerticalAngle) {
        _verticalAngle = -MaxVerticalAngle;
    }
}
