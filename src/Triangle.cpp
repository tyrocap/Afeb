//
// Created by adam on 2/16/21.
//

#include "Triangle.h"
#include <GL/glew.h>
#include <glm/gtx/transform.hpp>
#include <iostream>

using namespace Afeb;

Triangle::Triangle() : _vertexData{},
                       _vboID{} {
    glm::vec3 positions[cst::TRIANGLE_POINTS] = {
        glm::vec3(0.0f, 0.5f, 0.0f),
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.0f, 0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.0f, 0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(0.0f, 0.5f, 0.0f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f)};
    glm::vec3 color(0.8f, 0.2f, 0.1f);

    int idx = 0;
    for (int i = 0; i < cst::TRIANGLE_POINTS; ++i) {
        _vertexData[idx++] = positions[i].x;
        _vertexData[idx++] = positions[i].y;
        _vertexData[idx++] = positions[i].z;
        _vertexData[idx++] = color.x;
        _vertexData[idx++] = color.y;
        _vertexData[idx++] = color.z;
    }
    glGenBuffers(1, &_vboID);
    copyToBuffer();
}

Triangle::~Triangle() {
    if (_vboID != 0) {
        glDeleteBuffers(1, &_vboID);
    }
}

void Triangle::draw() const {
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    glEnableVertexAttribArray(cst::FIRST_ATTRIBUTE);
    glEnableVertexAttribArray(cst::SECOND_ATTRIBUTE);

    glVertexAttribPointer(cst::FIRST_ATTRIBUTE, cst::NUMBER_OF_COMPONENTS_PER_VERTEX,
        GL_FLOAT, GL_FALSE, cst::BYTE_OFFSET * sizeof(float), (void*)0);
    glVertexAttribPointer(cst::SECOND_ATTRIBUTE, cst::NUMBER_OF_COMPONENTS_PER_VERTEX,
        GL_FLOAT, GL_FALSE, cst::BYTE_OFFSET * sizeof(float),
        (void*)(cst::OFFSET_TO_NEXT_VERTEX_ATTRIB * sizeof(float)));

    glDrawArrays(GL_TRIANGLES, 0, cst::INDICES_TO_DRAW);

    glDisableVertexAttribArray(cst::FIRST_ATTRIBUTE);
    glDisableVertexAttribArray(cst::SECOND_ATTRIBUTE);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Triangle::transform(const glm::mat4& transMatrix) {

    glm::vec4 newPositions[cst::TRIANGLE_POINTS];
    int idx = 0, idx1 = 0; // from 18 in total, these need to access 0,1,2,6,7,8,12,13,14
    for (int i = 0; i < cst::TRIANGLE_POINTS; ++i) {
        glm::vec3 oldPos(_vertexData[idx], _vertexData[idx + 1], _vertexData[idx + 2]);
        newPositions[i] = transMatrix * glm::vec4(oldPos, 1.0);
        _vertexData[idx1] = newPositions[i].x;
        _vertexData[idx1 + 1] = newPositions[i].y;
        _vertexData[idx1 + 2] = newPositions[i].z;
        idx += 6;
        idx1 += 6;
    }
    copyToBuffer();
}

void Triangle::copyToBuffer() const {
    // Bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    // Copy the data to GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertexData), _vertexData, GL_STATIC_DRAW);

    // Unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Triangle::changeColor(const glm::vec3& color) {
    int idx = 3;
    for (int i = 0; i < (cst::TRIANGLE_DATA_LENGTH / 6); ++i) {
        _vertexData[idx++] = color.x;
        _vertexData[idx++] = color.y;
        _vertexData[idx++] = color.z;
        idx += 3;
    }
    copyToBuffer();
}

void Triangle::draw_bbox() {

    // Cube 1x1x1, centered on origin
    GLfloat vertices[] = {
        -0.5, -0.5, -0.5, 1.0,
        0.5, -0.5, -0.5, 1.0,
        0.5,  0.5, -0.5, 1.0,
        -0.5,  0.5, -0.5, 1.0,
        -0.5, -0.5,  0.5, 1.0,
        0.5, -0.5,  0.5, 1.0,
        0.5,  0.5,  0.5, 1.0,
        -0.5,  0.5,  0.5, 1.0,
    };
    unsigned int vbo_vertices;
    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLushort elements[] = {
        0, 1, 2, 3,
        4, 5, 6, 7,
        0, 4, 1, 5, 2, 6, 3, 7
    };
    unsigned int ibo_elements;
    glGenBuffers(1, &ibo_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    float
        min_x, max_x,
        min_y, max_y,
        min_z, max_z;
    min_x = max_x = _vertexData[0];
    min_y = max_y = _vertexData[1];
    min_z = max_z = _vertexData[2];
    for (int i = 0; i < cst::TRIANGLE_DATA_LENGTH; i += 3) {
        int indexX = i, indexY = i + 1, indexZ = 1 + 2;
        if (_vertexData[indexX] < min_x) min_x = _vertexData[indexX];
        if (_vertexData[indexX] > max_x) max_x = _vertexData[indexX];
        if (_vertexData[indexY] < min_y) min_y = _vertexData[indexY];
        if (_vertexData[indexY] > max_y) max_y = _vertexData[indexY];
        if (_vertexData[indexZ] < min_z) min_z = _vertexData[indexZ];
        if (_vertexData[indexZ] > max_z) max_z = _vertexData[indexZ];
    }
    glm::vec3 size = glm::vec3(max_x-min_x, max_y-min_y, max_z-min_z);
    glm::vec3 center = glm::vec3((min_x+max_x)/2, (min_y+max_y)/2, (min_z+max_z)/2);
    glm::mat4 transform = glm::translate(glm::mat4(1), center) * glm::scale(glm::mat4(1), size);

    /* Apply object's transformation matrix */
    /*
    glm::mat4 m = cameraMatrix * transform;
    glUniformMatrix4fv(uniform_m, 1, GL_FALSE, glm::value_ptr(m));
    */

    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,  // attribute
        4,                  // number of elements per vertex, here (x,y,z,w)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
    glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
    glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, (GLvoid*)(4*sizeof(GLushort)));
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, (GLvoid*)(8*sizeof(GLushort)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &vbo_vertices);
    glDeleteBuffers(1, &ibo_elements);
}