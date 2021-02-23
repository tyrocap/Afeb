//
// Created by adam on 2/23/21.
//

#ifndef AFEB__CAMERA3D_H
#define AFEB__CAMERA3D_H

#include <glm/glm.hpp>

namespace Afeb {
    class Camera3D {
    public:
        Camera3D(float fov, float aspect, float zNear, float zFar);
        Camera3D(float fov, float aspect, float zNear, float zFar, glm::vec3 position);

        void GetMatrices(glm::mat4& perspective, glm::mat4& view);

        void ChangePosition(int key) {
            const float cameraSpeed = 0.05f;
            if (key == 1) _position += cameraSpeed * glm::vec3(0.0f, 0.0f, 1.0f);
            if (key == 2) _position -= cameraSpeed * glm::vec3(0.0f, 0.0f, -1.0f);
            /*
            if (key == 3) _position -= glm::normalize(glm::cross(camFront, glm::vec3(0.0f, 0.0f, 1.0f)) * cameraSpeed);
            if (key == 4) _position += glm::normalize(glm::cross(camFront, glm::vec3(0.0f, 0.0f, 1.0f)) * cameraSpeed);
             */
        }

    private:
        glm::vec3 _position;
        float _fov;
        float _aspect;
        float _zNear;
        float _zFar;
    };
}

#endif //AFEB__CAMERA3D_H
