//
// Created by adam on 2/15/21.
//

#ifndef AFEB_GLSLPROGRAM_H
#define AFEB_GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>

class GLSLProgram {
public:
    GLSLProgram();
    ~GLSLProgram();

    void compileShaders(const std::string& vertexShaderFilePath,
                        const std::string& fragmentShaderFilePath);

    void linkShaders();

    void use();
    void unuse();
private:
    void compileShader(const std::string& filePath, unsigned int id);
    unsigned int _programID;
    unsigned int _vertexShaderID;
    unsigned int _fragmentShaderID;


};


#endif //AFEB_GLSLPROGRAM_H
