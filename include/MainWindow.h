//
// Created by adam on 2/14/21.
//

#ifndef AFEB_MAINWINDOW_H
#define AFEB_MAINWINDOW_H

#include <GL/glew.h>
#include <SDL.h>
#include "CoordSystem.h"
#include "GlslProgram.h"
#include "Triangle.h"

struct Coords {
    int x;
    int y;
};


namespace Afeb {
    enum class WindowState {
        ON, OFF
    };


    class MainWindow {
    public:
        MainWindow();
        ~MainWindow();

        void run();


    private:
        bool _flags[4] = {0};
        glm::vec3 _color = glm::vec3(0.0f);
        glm::vec3 _translate{};
        glm::vec3 _scale{};
        float _rotate{};

        float _curTime = 1.0f;

        void initSystems();
        void mainLoop();
        void drawWindow();
        void processInput();
        void initShaders();

        SDL_Window* _window;
        int _screenWidth;
        int _screenHeight;

        WindowState _windowState;
        CoordSystem _coordSystem;

        GlslProgram _shaderProgram;


    };
}


#endif //AFEB_MAINWINDOW_H
