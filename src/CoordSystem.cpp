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


void CoordSystem::init(float pt1X, float pt1Y,
                       float pt2X, float pt2Y,
                       float pt3X, float pt3Y,
                       float pt4X, float pt4Y
                       ) {
    _pt1X = pt1X;
    _pt1Y = pt1Y;
    _pt2X = pt2X;
    _pt2Y = pt2Y;
    _pt3X = pt3X;
    _pt3Y = pt3Y;
    _pt4X = pt4X;
    _pt4Y = pt4Y;

    // Generate vertex buffer if it doesn't exist
    if (_vboID == 0) {
        glGenBuffers(1, &_vboID);
    }
    float vertexData[8];
    // First triangle
    vertexData[0] = _pt1X;
    vertexData[1] = _pt1Y;
    vertexData[2] = _pt2X;
    vertexData[3] = _pt2Y;
    vertexData[4] = _pt3X;
    vertexData[5] = _pt3Y;
    vertexData[6] = _pt4X;
    vertexData[7] = _pt4Y;

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void CoordSystem::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_LINES, 0, 8);

    //glDisableVertexArrayAttrib();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


