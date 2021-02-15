//
// Created by adam on 2/14/21.
//

#ifndef AFEB_COORDSYSTEM_H
#define AFEB_COORDSYSTEM_H

#include <GL/glew.h>
#include <glm/vec3.hpp>


class CoordSystem {
public:
    CoordSystem();
    ~CoordSystem();

    void init(glm::vec3 pt1, glm::vec3 pt2, glm::vec3 pt3, glm::vec3 pt4, glm::vec3 color);
    void draw();

private:
    // position coords (xyz)
   float _pt1X, _pt1Y, _pt1Z,
         _pt2X, _pt2Y, _pt2Z,
         _pt3X, _pt3Y, _pt3Z,
         _pt4X, _pt4Y, _pt4Z;
    // color
   float _clR, _clG, _clB;

    unsigned int _vboID;




};


#endif //AFEB_COORDSYSTEM_H
