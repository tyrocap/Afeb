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

    void init(float pt1X, float pt1Y,
              float pt2X, float pt2Y,
              float pt3X, float pt3Y,
              float pt4X, float pt4Y);
    void draw();

private:
   float _pt1X, _pt1Y, _pt2X, _pt2Y, _pt3X,  _pt3Y, _pt4X,  _pt4Y;

    unsigned int _vboID;




};


#endif //AFEB_COORDSYSTEM_H
