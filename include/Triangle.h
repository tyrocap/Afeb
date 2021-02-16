//
// Created by adam on 2/16/21.
//

#ifndef AFEB_TRIANGLE_H
#define AFEB_TRIANGLE_H
#include <glm/glm.hpp>

class Triangle {
public:
    Triangle(glm::vec3 positions[], glm::vec3 color);
    ~Triangle();

    void draw();
    void copyToBuffer();
    void transform(glm::mat4 &transMatrix);

private:
    glm::vec3 _positions[3];
    glm::vec3 _color;
    unsigned int _vboID;
};


#endif //AFEB_TRIANGLE_H
