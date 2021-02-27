//
// Created by adam on 2/23/21.
//

#ifndef AFEB__CAMERA3D_H
#define AFEB__CAMERA3D_H

#include <glm/detail/type_quat.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace Afeb {
    class Camera3D {
    public:
        Camera3D();

        // position
        const glm::vec3& getPosition() const;
        void setPosition(const glm::vec3& position);
        void offsetPosition(const glm::vec3& offset);

        // aspect ratio
        void setViewportAspectRatio(float viewportAspectRatio);

        // movement
        glm::vec3 forward() const;
        glm::vec3 right() const;
        glm::vec3 up() const;

        // matrix
        glm::mat4 matrix() const;
        glm::mat4 projection() const;

        // input
        void processMouseMovement(float xOffset, float yOffset);
        void processWheelMovement(int direction);
        void updateCameraVectors();

    private:
        float _fieldOfView,
            _nearPlane,
            _farPlane,
            _viewportAspectRatio,
            _mouseSensitivity = 0.1f,
            _yaw = -90.0f,
            _pitch = 0.0f,
            _zoom = 1.0f;

        glm::vec3 _position,
            _front,
            _right,
            _up,
            _worldUp;
    };
} // namespace Afeb

#endif //AFEB__CAMERA3D_H
