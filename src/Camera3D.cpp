//
// Created by adam on 2/23/21.
//

#include "Camera3D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Afeb {
    Camera3D::Camera3D(float fov, float aspect, float zNear, float zFar)
        : _fov(fov), _aspect(aspect), _zNear(zNear), _zFar(zFar), _position(glm::vec3(0.0f, 0.0f, 1.0f)) {
    };

    Camera3D::Camera3D(float fov, float aspect, float zNear, float zFar, glm::vec3 position)
        : _fov(fov), _aspect(aspect), _zNear(zNear), _zFar(zFar), _position(position) {
    }

    void Camera3D::GetMatrices(glm::mat4& perspective, glm::mat4& view) {
        perspective = glm::perspective(_fov, _aspect, _zNear, _zFar);
        view = perspective * glm::lookAt(_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
}

