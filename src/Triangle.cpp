//
// Created by adam on 2/16/21.
//

#include "Triangle.h"
#include <GL/glew.h>

namespace Afeb {

    namespace cst {
        const int TRIANGLE_DATA_LENGTH = 18; // 6 per point (3 position & 3 color)
        const int INDICES_TO_DRAW = 3;
        const int NUMBER_OF_COMPONENTS_PER_VERTEX = 3;
        const int BYTE_OFFSET = 6;
        const int OFFSET_TO_NEXT_VERTEX_ATTRIB = 3;
        const int FIRST_ATTRIBUTE = 0; // position
        const int SECOND_ATTRIBUTE = 1; // color

    } // namespace cst

    Triangle::Triangle(glm::vec3 positions[], glm::vec3 color) {
        for (int i = 0; i < cst::TRIANGLE_POINTS; ++i) {
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

    void Triangle::transform(glm::mat4& transMatrix) {
        glm::vec4 newPositions[cst::TRIANGLE_POINTS];
        for (int i = 0; i < cst::TRIANGLE_POINTS; ++i) {
            newPositions[i] = transMatrix * glm::vec4(_positions[i], 1.0);
            _positions[i].x = newPositions[i].x;
            _positions[i].y = newPositions[i].y;
            _positions[i].z = newPositions[i].z;
        }
        copyToBuffer();
    }

    void Triangle::copyToBuffer() {
        float vertexData[cst::TRIANGLE_DATA_LENGTH];
        int idx = 0;
        for (int i = 0; i < cst::TRIANGLE_POINTS; ++i) {
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
} // namespace Afeb
