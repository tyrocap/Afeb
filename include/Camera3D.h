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

        /**
         * The position of the camera
         */
        const glm::vec3& position() const;
        void setPosition(const glm::vec3& position);
        void offsetPosition(const glm::vec3& offset);

        /**
         * The vertical viewing angle of the camera, in degress
         * Determines how 'wide' the view of the camera is. Large
         * angles appear to be zoomed out, as the camera has a
         * wide view. Small values appear to be zoomed in, as the
         * camera has a very narrow view.
         * The value must be btw 0 and 180.
         */
         float fieldOfView() const;
         void setFieldOfView(float fieldOfView);

         /**
          * The closest visible distance from the camera
          * Objects that are closer to the camera than the near plane
          * distance will not be visible.
          * Value must be greater than 0.
          */
          float nearPlane() const;

        /**
         * The farthest visible distance from the camera
         * Objects that are further away from the camera than the far plane
         * distance will not be visible.
         * Value must be greater than the near plane.
         */
        float farPlane() const;

        /**
         * Sets the near and far plane distances.
         */
         void setNearAndFarPlanes(float nearPlane, float farPlane);

         /**
          * A rotation matrix that determines the direction the camera is
          * looking. Does not include translation (the camera's position).
          */
          glm::mat4 orientation() const;

          /**
           * Offsets the camera orientation.
           * The verticle angle is constrained between 85 deg and -85 deg
           * to avoid gimbal lock.
           * @param upAngle - the angle (in degrees) to offset upwards.
           *    Negative values are downwards.
           * @param rightAngle - the angle (in degrees) to offset rightwards.
           *    Negative values are leftwards.
           */
           void offsetOrientation(float upAngle, float rightAngle);

           /**
            * Orients the camera so that it is directly facing 'position'.
            * @param position - the position to look at
            */
            void lookAt(glm::vec3 position);

            /**
             * The width divided by the height of the screen/window/viewport.
             * Incorrect values will make the 3D scene look stretched.
             */
             float viewportAspectRatio() const;
             void setViewportAspectRatio(float viewportAspectRatio);

             /**
              * A unit vector representing the direction the camera is facing.
              */
              glm::vec3 forward() const;

              /**
              * A unit vector representing the direction to the right of the camera.
              */
              glm::vec3 right() const;

              /**
              * A unit vector representing the direction out of the top of the camera.
              */
              glm::vec3 up() const;

              /**
               * The combined camera transformation matrix, including perspective projection.
               * This is the complete matrix to use in the vertex shader.
               */
               glm::mat4 matrix() const;

               /**
                * The perspective projection transformation matrix.
                */
                glm::mat4 projection() const;

                /**
                 * The translation and rotation matrix of the camera.
                 * Same as the 'matrix' method, except the return value
                 * does not include the projection transformation.
                 */
                 glm::mat4 view() const;

                 void processMouseMovement(float xOffset, float yOffset) {
                     xOffset *= _mouseSensitivity;
                     yOffset *= _mouseSensitivity;
                     std::cout << "xOffset and yOffset: " << xOffset << ", " << yOffset << std::endl;
                     _yaw += xOffset;
                     _pitch += yOffset;
                     if (_pitch > 89.0f) {
                         _pitch = 89.0f;
                     }
                     if (_pitch < -89.0f) {
                         _pitch = -89.0f;
                     }
                     updateCameraVectors();
                     std::cout << "YAW AND PITCH: " << _yaw << ", " << _pitch << std::endl;
                 }
                 void updateCameraVectors() {
                     glm::vec3 front;
                     front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
                     front.y = sin(glm::radians(_pitch));
                     front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
                     std::cout << "front: " << glm::to_string(front) << std::endl;
                     _front = glm::normalize(front);
                     _right = glm::normalize(glm::cross(_front, _worldUp));
                     _up = glm::normalize(glm::cross(_right, _front));
                 }

    private:
        glm::vec3 _position;
        float _horizontalAngle;
        float _verticalAngle;
        float _fieldOfView;
        float _nearPlane;
        float _farPlane;
        float _viewportAspectRatio;

        //
        glm::vec3 _front;
        glm::vec3 _right;
        glm::vec3 _up;
        glm::vec3 _worldUp;
        float _mouseSensitivity = 0.0004f;
        float _yaw = -90.0f, _pitch = 0.0f;

        void normalizeAngles();
    };
}

#endif //AFEB__CAMERA3D_H
