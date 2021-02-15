//
// Created by adam on 2/14/21.
//

#include "CoordSystem.h"
#include <glm/vec3.hpp>

CoordSystem::CoordSystem() {
    _vboID = 0;
}

CoordSystem::~CoordSystem() {
    if (_vboID != 0) {
        glDeleteBuffers(1, &_vboID);
    }
}

void CoordSystem::init(glm::vec3 pt1, glm::vec3 pt2, glm::vec3 pt3, glm::vec3 pt4, glm::vec3 color) {
    // Set position coords
    _pt1X = pt1.x;
    _pt1Y = pt1.y;
    _pt1Z = pt1.z;
    _pt2X = pt2.x;
    _pt2Y = pt2.y;
    _pt2Z = pt2.z;
    _pt3X = pt3.x;
    _pt3Y = pt3.y;
    _pt3Z = pt3.z;
    _pt4X = pt4.x;
    _pt4Y = pt4.y;
    _pt4Z = pt4.z;

    // Set color
    _clR = color.x;
    _clG = color.y;
    _clB = color.z;

    // coord system X axis number lines position/color
    float tempX = -1.0f;
    float tempY = 0.02f;
    int idx = 0;
    for (int i = 0; i < 21; ++i) {
        for (int j = 0; j < 2; ++j) {
            _coordNumbers[idx++] = tempX; // position: X
            _coordNumbers[idx++] = tempY; // position: Y
            _coordNumbers[idx++] = 0.0f; // position: Z
            _coordNumbers[idx++] = 0.0f; // color: R
            _coordNumbers[idx++] = 0.0f; // color: G
            _coordNumbers[idx++] = 0.0f; // color: B
            tempY *= -1;
        }
        tempX += 0.1f;
    }

    // Generate vertex buffer if it doesn't exist
    if (_vboID == 0) {
        glGenBuffers(1, &_vboID);
    }
    float vertexData[276];
    // Set coordinates of X and Y axes
    idx = 0;
    vertexData[idx++] = _pt1X;
    vertexData[idx++] = _pt1Y;
    vertexData[idx++] = _pt1Z;
    vertexData[idx++] = _clR;
    vertexData[idx++] = _clG;
    vertexData[idx++] = _clB;

    vertexData[idx++] = _pt2X;
    vertexData[idx++] = _pt2Y;
    vertexData[idx++] = _pt2Z;
    vertexData[idx++] = _clR;
    vertexData[idx++] = _clG;
    vertexData[idx++] = _clB;

    vertexData[idx++] = _pt3X;
    vertexData[idx++] = _pt3Y;
    vertexData[idx++] = _pt3Z;
    vertexData[idx++] = _clR;
    vertexData[idx++] = _clG;
    vertexData[idx++] = _clB;

    vertexData[idx++] = _pt4X;
    vertexData[idx++] = _pt4Y;
    vertexData[idx++] = _pt4Z;
    vertexData[idx++] = _clR;
    vertexData[idx++] = _clG;
    vertexData[idx++] = _clB;

    for (int i = 0; i < 252; ++i) {
        vertexData[idx++] = _coordNumbers[i];
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void CoordSystem::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    glEnableVertexAttribArray(0); // position
    glEnableVertexAttribArray(1); // color

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glDrawArrays(GL_LINES, 0, 46);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


