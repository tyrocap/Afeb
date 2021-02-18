//
// Created by adam on 2/16/21.
//

#ifndef AFEB_TRIANGLE_H
#define AFEB_TRIANGLE_H
#include <glm/glm.hpp>

namespace Afeb {

    namespace cst {
        const int TRIANGLE_POINTS = 3;
    }

    class Triangle {
    public:
        Triangle(glm::vec3 positions[], glm::vec3 color);
        ~Triangle();

        void draw();
        void copyToBuffer();
        void transform(glm::mat4 &transMatrix);

    private:
        glm::vec3 _positions[cst::TRIANGLE_POINTS];
        glm::vec3 _color;
        unsigned int _vboID;
    };

}


#endif //AFEB_TRIANGLE_H
