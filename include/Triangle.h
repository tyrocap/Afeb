//
// Created by adam on 2/16/21.
//

#ifndef AFEB_TRIANGLE_H
#define AFEB_TRIANGLE_H
#include <glm/glm.hpp>

namespace Afeb {

    namespace cst {
        const int INDICES_TO_DRAW = 12;
        const int TRIANGLE_DATA_LENGTH = INDICES_TO_DRAW * 6; // 6 per point (3 position & 3 color)
        const int NUMBER_OF_COMPONENTS_PER_VERTEX = 3;
        const int BYTE_OFFSET = 6;
        const int OFFSET_TO_NEXT_VERTEX_ATTRIB = 3;
        const int FIRST_ATTRIBUTE = 0; // position
        const int SECOND_ATTRIBUTE = 1; // color
        // TODO:
        const int TRIANGLE_POINTS = 12;
    } // namespace cst

    class Triangle {
    public:
        Triangle();
        ~Triangle();

        void changeColor(const glm::vec3 &color);
        void draw() const;
        void draw_bbox();
        void transform(const glm::mat4 &transMatrix);

    private:
        void copyToBuffer() const;

        float _vertexData[cst::TRIANGLE_DATA_LENGTH];
        unsigned int _vboID;
    };

}


#endif //AFEB_TRIANGLE_H
