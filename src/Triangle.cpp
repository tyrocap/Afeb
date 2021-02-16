//
// Created by adam on 2/16/21.
//

#include "Triangle.h"
#include <GL/glew.h>
#include <iostream>


Triangle::Triangle(glm::vec3 positions[], glm::vec3 color) {
    for (int i = 0; i < 3; ++i) {
        _positions[i] = positions[i];
    }
    _color = color;
    glGenBuffers(1, &_vboID);
    copyToBuffer();
}


Triangle::~Triangle() {
    if (_vboID != 0) {
        glDeleteBuffers(1, &_vboID);
    }
}

void Triangle::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    glEnableVertexAttribArray(0); // position
    glEnableVertexAttribArray(1); // color

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Triangle::transform(glm::mat4 &transMatrix) {
    glm::vec4 newPositions[3];
    for (int i = 0; i < 3; ++i) {
        newPositions[i] = transMatrix * glm::vec4(_positions[i], 1.0);
        _positions[i].x = newPositions[i].x;
        _positions[i].y = newPositions[i].y;
        _positions[i].z = newPositions[i].z;
    }
    copyToBuffer();
}

void Triangle::copyToBuffer() {
    float vertexData[18];
    int idx = 0;
    for (int i = 0; i < 3; ++i) {
        vertexData[idx++] = _positions[i].x;
        vertexData[idx++] = _positions[i].y;
        vertexData[idx++] = _positions[i].z;
        vertexData[idx++] = _color.x;
        vertexData[idx++] = _color.y;
        vertexData[idx++] = _color.z;
    }
    // Bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    // Copy the data to GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // Unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}