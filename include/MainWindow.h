//
// Created by adam on 2/14/21.
//

#ifndef AFEB_MAINWINDOW_H
#define AFEB_MAINWINDOW_H

#include <SDL.h>
#include <GL/glew.h>
#include "CoordSystem.h"
#include "GLSLProgram.h"

enum class WindowState {
    ON, OFF
};

class MainWindow { //MainGame
public:
    MainWindow();
    ~MainWindow();

    void run();


private:

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

    GLSLProgram _shaderProgram;

};


#endif //AFEB_MAINWINDOW_H
