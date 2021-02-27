//
// Created by adam on 2/14/21.
//

#ifndef AFEB_MAINWINDOW_H
#define AFEB_MAINWINDOW_H

#include <GL/glew.h>
#include <SDL.h>
#include <imgui.h>
#include "Camera3D.h"
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
        // TODO:
        bool _flags[5] = {0};

        // TODO: since these dont have anything to do
        // with MainWindow, they could be declared
        // static in the source file.
        glm::vec3 _color = glm::vec3(0.0f);
        glm::vec3 _translate{};
        glm::vec3 _scale{};
        float _rotate{};
        // End

        bool _leftMousePressed = false;

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
        Camera3D _camera;
    };
}


#endif //AFEB_MAINWINDOW_H
