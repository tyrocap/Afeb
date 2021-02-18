//
// Created by adam on 2/14/21.
//

#include "CoordSystem.h"
#include <glm/vec3.hpp>

namespace Afeb {
    CoordSystem::CoordSystem() {
        _vboID = 0;
    }

    // TODO: apply rule of 3
    CoordSystem::~CoordSystem() {
        if (_vboID != 0) {
            glDeleteBuffers(1, &_vboID);
        }
    }

    void CoordSystem::init() {

        int index = 0;
        int const XY_AXES_DATA_LENGTH = 24;

        // Set X and Y axes points (= position and color coords)
        float xYCoords[XY_AXES_DATA_LENGTH] = {
            -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f
        };
        for (int i = 0; i < XY_AXES_DATA_LENGTH; ++i) {
            _xYCoordsData[index++] = xYCoords[i];
        }

        // Set X axis number lines points
        float tempX = -1.0f; // left edge of screen in OpenGL
        float tempY = 0.01f; // half height of a (vertical) number line
        for (int i = 0; i < 21; ++i) {
            for (int j = 0; j < 2; ++j) {
                _xYCoordsData[index++] = tempX; // position: X
                _xYCoordsData[index++] = tempY; // position: Y
                _xYCoordsData[index++] = 0.0f; // position: Z
                _xYCoordsData[index++] = 0.0f; // color: R
                _xYCoordsData[index++] = 0.0f; // color: G
                _xYCoordsData[index++] = 0.0f; // color: B
                tempY *= -1; // Ensure the next point draws the other half height
            }
            tempX += 0.1f; // move towards right edge '0.1f' at a time
        }

        // Set Y axis number lines points
        tempX = 0.01f;
        tempY = -1.0f; // bottom edge of screen in OpenGL
        for (int i = 0; i < 21; ++i) {
            for (int j = 0; j < 2; ++j) {
                _xYCoordsData[index++] = tempX; // position: X
                _xYCoordsData[index++] = tempY; // position: Y
                _xYCoordsData[index++] = 0.0f; // position: Z
                _xYCoordsData[index++] = 0.0f; // color: R
                _xYCoordsData[index++] = 0.0f; // color: G
                _xYCoordsData[index++] = 0.0f; // color: B
                tempX *= -1;
            }
            tempY += 0.1f; // move towards upper edge '0.1f' at a time
        }

        // Generate vertex buffer if it doesn't exist
        if (_vboID == 0) {
            glGenBuffers(1, &_vboID);
        }

        // Bind buffer
        glBindBuffer(GL_ARRAY_BUFFER, _vboID);

        // Copy the data to GPU
        glBufferData(GL_ARRAY_BUFFER, sizeof(_xYCoordsData), _xYCoordsData, GL_STATIC_DRAW);

        // Unbind buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void CoordSystem::draw() {
        init();

        // Bind buffer
        glBindBuffer(GL_ARRAY_BUFFER, _vboID);

        // Enable attributes; They are off by default
        glEnableVertexAttribArray(0); // position
        glEnableVertexAttribArray(1); // color

        // Tell OpenGL how to interpret the data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        // Draw lines
        glDrawArrays(GL_LINES, 0, 88);

        // Clean up
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

} // namespace Afeb
