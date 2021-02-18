//
// Created by adam on 2/14/21.
//

#ifndef AFEB_COORDSYSTEM_H
#define AFEB_COORDSYSTEM_H

#include <GL/glew.h>
#include <glm/vec3.hpp>

constexpr int COORD_SYSTEM_DATA_LENGTH = 528;

namespace Afeb {
    class CoordSystem {
    public:
        CoordSystem();
        ~CoordSystem();

        void draw();

    private:
        void init();

        float _xYCoordsData[COORD_SYSTEM_DATA_LENGTH];
        unsigned int _vboID;
    };

} // namespace Afeb

#endif //AFEB_COORDSYSTEM_H
