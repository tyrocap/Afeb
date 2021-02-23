//
// Created by adam on 2/15/21.
//

#ifndef AFEB_GLSLPROGRAM_H
#define AFEB_GLSLPROGRAM_H

#include <GL/glew.h>
#include <string>

namespace Afeb {
    class GlslProgram {
    public:
        GlslProgram();
        ~GlslProgram();

        void compileShaders(const std::string& vertexShaderFilePath,
            const std::string& fragmentShaderFilePath);

        void linkShaders();
        unsigned int getID();

        void use();
        void unuse();

    private:
        void compileShader(const std::string& filePath, unsigned int id);
        unsigned int _programID;
        unsigned int _vertexShaderID;
        unsigned int _fragmentShaderID;
    };

} // namespace Afeb

#endif //AFEB_GLSLPROGRAM_H
