//
// Created by adam on 2/14/21.
//

#include "../include/MainWindow.h"
#include <iostream>
#include "Error.h"



MainWindow::MainWindow() {
    _window = nullptr;
    _screenWidth = 1224;
    _screenHeight = 868;
    _windowState = WindowState::ON;

}

MainWindow::~MainWindow() {

}

void MainWindow::run() {
    initSystems();
    _coordSystem.init(glm::vec3(-1.0f, 0.0f, 1.0f),
                      glm::vec3(1.0f, 0.0f, 1.0f),
                      glm::vec3(0.0f, 1.0f,  1.0f),
                      glm::vec3(0.0f, -1.0f, 1.0f),
                      glm::vec3(0.0f, 0.0f, 0.0f));
    mainLoop();
}

void MainWindow::initSystems() {
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow("Afeb", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                     _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
    if (_window == nullptr) {
        fatalError("SDL Window could not be created!");
    }

    // OpenGL initilization logic
    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        fatalError("SDL_GL context could not be created!");
    }

    GLenum error = glewInit();
    if (error != GLEW_OK) {
        fatalError("Could not initilize glew!");
    }

    // set up two buffers
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0);

    initShaders();

}

void MainWindow::mainLoop() {
    while (_windowState != WindowState::OFF) {
        processInput();
        drawWindow();
    }

}

void MainWindow::processInput() {
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                _windowState = WindowState::OFF;
                break;
            case SDL_MOUSEMOTION:
                std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
        }
    }

}

void MainWindow::drawWindow() {
    // Set the base depth to 1.0
    glClearDepth(1.0);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Shaders
    _shaderProgram.use();

    glLineWidth(2);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    _coordSystem.draw();

    _shaderProgram.unuse();

    // Swap buffers and draw everything to the screen
    SDL_GL_SwapWindow(_window);
}

void MainWindow::initShaders() {
    _shaderProgram.compileShaders("./shaders/basic.vert",
                                  "./shaders/basic.frag");
    _shaderProgram.linkShaders();
}
