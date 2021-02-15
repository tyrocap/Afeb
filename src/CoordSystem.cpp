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

    // Generate vertex buffer if it doesn't exist
    if (_vboID == 0) {
        glGenBuffers(1, &_vboID);
    }
    float vertexData[24];
    // Set coordinates
    vertexData[0] = _pt1X;
    vertexData[1] = _pt1Y;
    vertexData[2] = _pt1Z;
    vertexData[3] = _clR;
    vertexData[4] = _clG;
    vertexData[5] = _clB;

    vertexData[6] = _pt2X;
    vertexData[7] = _pt2Y;
    vertexData[8] = _pt2Z;
    vertexData[9] = _clR;
    vertexData[10] = _clG;
    vertexData[11] = _clB;

    vertexData[12] = _pt3X;
    vertexData[13] = _pt3Y;
    vertexData[14] = _pt3Z;
    vertexData[15] = _clR;
    vertexData[16] = _clG;
    vertexData[17] = _clB;

    vertexData[18] = _pt4X;
    vertexData[19] = _pt4Y;
    vertexData[20] = _pt4Z;
    vertexData[21] = _clR;
    vertexData[22] = _clG;
    vertexData[23] = _clB;

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

    glDrawArrays(GL_LINES, 0, 4);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


