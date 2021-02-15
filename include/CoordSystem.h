//
// Created by adam on 2/14/21.
//

#ifndef AFEB_COORDSYSTEM_H
#define AFEB_COORDSYSTEM_H

#include <GL/glew.h>


class CoordSystem {
public:
    CoordSystem();
    ~CoordSystem();

    void init(float x, float y, float width, float height);
    void draw();

private:
    float _x,
          _y,
          _width,
          _height;
    unsigned int _vboID;




};


#endif //AFEB_COORDSYSTEM_H
