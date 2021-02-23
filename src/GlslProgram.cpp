//
// Created by adam on 2/15/21.
//

#include "GlslProgram.h"
#include <fstream>
#include <vector>
#include "Error.h"

namespace Afeb {
    GlslProgram::GlslProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
    {

    }

    GlslProgram::~GlslProgram()
    {

    }

    void GlslProgram::compileShaders(const std::string& vertexShaderFilePath,
        const std::string& fragmentShaderFilePath)
    {
        _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        if (_vertexShaderID == 0) {
            fatalError("Vertex shader failed to be created!");
        }
        _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        if (_fragmentShaderID == 0) {
            fatalError("Fragment shader failed to be created!");
        }

        compileShader(vertexShaderFilePath, _vertexShaderID);
        compileShader(fragmentShaderFilePath, _fragmentShaderID);
    }

    void GlslProgram::linkShaders()
    {
        _programID = glCreateProgram();
        glAttachShader(_programID, _vertexShaderID);
        glAttachShader(_programID, _fragmentShaderID);

        glLinkProgram(_programID);

        // Error checking
        int isLinked = 0;
        glGetProgramiv(_programID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            int maxLength = 0;
            glGetShaderiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<char> errorLog(maxLength);
            glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

            // Provide info log
            glDeleteProgram(_programID);
            glDeleteShader(_vertexShaderID);
            glDeleteShader(_fragmentShaderID);

            std::printf("%s\n", &(errorLog[0]));
            fatalError("Shaders failed to link!");
        }
        // Free up resources
        glDetachShader(_programID, _vertexShaderID);
        glDetachShader(_programID, _fragmentShaderID);

        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);
    }

    void GlslProgram::compileShader(const std::string& filePath, unsigned int id)
    {
        std::ifstream vertexFile(filePath);
        if (vertexFile.fail()) {
            perror(filePath.c_str());
            fatalError("Failed to open " + filePath);
        }

        std::string fileContents = "";
        std::string line;
        while (std::getline(vertexFile, line)) {
            fileContents += line + "\n";
        }
        vertexFile.close();

        const char* contentsPtr = fileContents.c_str();
        glShaderSource(id, 1, &contentsPtr, nullptr);
        glCompileShader(id);

        int success = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            int maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

            // Provide info log in whatever manor you think best
            glDeleteShader(id);

            std::printf("%s\n", &(errorLog[0]));
            fatalError("Shader " + filePath + " failed to compile!");
        }
    }

    void GlslProgram::use()
    {
        glUseProgram(_programID);
        glEnableVertexAttribArray(0);
    }

    void GlslProgram::unuse()
    {
        glUseProgram(0);
        glDisableVertexAttribArray(0);
    }

    unsigned int GlslProgram::getID() {
        return _programID;
    }
} // namespace Afeb
