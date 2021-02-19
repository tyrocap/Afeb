//
// Created by adam on 2/16/21.
//

#ifndef AFEB_TRIANGLE_H
#define AFEB_TRIANGLE_H
#include <glm/glm.hpp>

namespace Afeb {

    namespace cst {
        const int TRIANGLE_DATA_LENGTH = 18; // 6 per point (3 position & 3 color)
        const int INDICES_TO_DRAW = 3;
        const int NUMBER_OF_COMPONENTS_PER_VERTEX = 3;
        const int BYTE_OFFSET = 6;
        const int OFFSET_TO_NEXT_VERTEX_ATTRIB = 3;
        const int FIRST_ATTRIBUTE = 0; // position
        const int SECOND_ATTRIBUTE = 1; // color
        const int TRIANGLE_POINTS = 3;
    } // namespace cst

    class Triangle {
    public:
        Triangle(const glm::vec3* positions, const glm::vec3* color);
        ~Triangle();

        void draw();
        void copyToBuffer();
        void transform(const glm::mat4 &transMatrix);

    private:
        float _vertexData[cst::TRIANGLE_DATA_LENGTH];
        unsigned int _vboID;
    };

}


#endif //AFEB_TRIANGLE_H
