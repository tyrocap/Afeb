//
// Created by adam on 2/14/21.
//

#include "CoordSystem.h"

CoordSystem::CoordSystem() {
    _vboID = 0;
}

CoordSystem::~CoordSystem() {
    if (_vboID != 0) {
        glDeleteBuffers(1, &_vboID);
    }
}


void CoordSystem::init(float pt1X, float pt1Y, float pt1Z,
                       float pt2X, float pt2Y, float pt2Z,
                       float pt3X, float pt3Y, float pt3Z,
                       float pt4X, float pt4Y, float pt4Z
                       ) {
    _pt1X = pt1X;
    _pt1Y = pt1Y;
    _pt1Z = pt1Z;
    _pt2X = pt2X;
    _pt2Y = pt2Y;
    _pt2Z = pt2Z;
    _pt3X = pt3X;
    _pt3Y = pt3Y;
    _pt3Z = pt3Z;
    _pt4X = pt4X;
    _pt4Y = pt4Y;
    _pt4Z = pt4Z;

    // Generate vertex buffer if it doesn't exist
    if (_vboID == 0) {
        glGenBuffers(1, &_vboID);
    }
    float vertexData[12];
    // First triangle
    vertexData[0] = _pt1X;
    vertexData[1] = _pt1Y;
    vertexData[2] = _pt1Z;
    vertexData[3] = _pt2X;
    vertexData[4] = _pt2Y;
    vertexData[5] = _pt2Z;
    vertexData[6] = _pt3X;
    vertexData[7] = _pt3Y;
    vertexData[8] = _pt3Z;
    vertexData[9] = _pt4X;
    vertexData[10] = _pt4Y;
    vertexData[11] = _pt4Z;

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void CoordSystem::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_LINES, 0, 4);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


