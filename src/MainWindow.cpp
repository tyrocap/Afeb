//
// Created by adam on 2/14/21.
//

#include "../include/MainWindow.h"
#include <iostream>

// TODO: create an error handling class
void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Enter any key to quit..";
    int tmp;
    std::cin >> tmp;
    SDL_Quit();
}

MainWindow::MainWindow() {
    _window = nullptr;
    _screenWidth = 1024;
    _screenHeight = 768;
    _windowState = WindowState::ON;

}

MainWindow::~MainWindow() {

}

void MainWindow::run() {
    initSystems();

    mainLoop();
}

void MainWindow::initSystems() {
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow("Afeb", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                     _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
    if (_window == nullptr) {
        fatalError("SDL Window could not be created!");
    }


}

void MainWindow::mainLoop() {
    while (_windowState != WindowState::OFF) {
        processInput();
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
