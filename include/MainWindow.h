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


    class MainWindow { //MainGame
    public:
        MainWindow();
        ~MainWindow();

        void run();


    private:
        glm::vec3 _color;
        glm::vec3 _translate;
        glm::vec3 _scale;
        float _rotate;

        void initSystems();
        void mainLoop(); // gameLoop
        void drawWindow(); // drawGame
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
