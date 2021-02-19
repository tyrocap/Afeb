//
// Created by adam on 2/16/21.
//

#include "Triangle.h"
#include <GL/glew.h>
#include <iostream>

namespace Afeb {

    namespace cst {
    }

    Triangle::Triangle(const glm::vec3* positions, const glm::vec3* color) {
        int idx = 0;
        for (int i = 0; i < cst::TRIANGLE_POINTS; ++i) {
            _vertexData[idx++] = positions[i].x;
            _vertexData[idx++] = positions[i].y;
            _vertexData[idx++] = positions[i].z;
            _vertexData[idx++] = color->x;
            _vertexData[idx++] = color->y;
            _vertexData[idx++] = color->z;
        }
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
        int idx = 0, idx1 = 0; // from 18 total, these need to access 0,1,2,6,7,8,12,13,14
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

    void Triangle::copyToBuffer() {
        // Bind buffer
        glBindBuffer(GL_ARRAY_BUFFER, _vboID);

        // Copy the data to GPU
        glBufferData(GL_ARRAY_BUFFER, sizeof(_vertexData), _vertexData, GL_STATIC_DRAW);

        // Unbind buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
} // namespace Afeb
