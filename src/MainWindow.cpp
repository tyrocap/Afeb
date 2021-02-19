//
// Created by adam on 2/14/21.
//

#include "../include/MainWindow.h"

#include <glm/ext/matrix_transform.hpp>
#include <iostream>

#include "Error.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"


namespace Afeb {

    namespace cst {
        const int SCREEN_WIDTH = 1224;
        const int SCREEN_HEIGHT = 868;
        const int OPENGL_LINE_WIDTH = 2;
    } // namespace cst

    MainWindow::MainWindow() {
        _window = nullptr;
        _screenWidth = cst::SCREEN_WIDTH;
        _screenHeight = cst::SCREEN_HEIGHT;
        _windowState = WindowState::ON;
        _temp = true;
        _speed = 23.0f;
    }

    MainWindow::~MainWindow() {
        _window = nullptr;
    }

    void MainWindow::run() {
        initSystems();
        mainLoop();

        // Dear ImGui clean up
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void MainWindow::initSystems() {
        SDL_Init(SDL_INIT_EVERYTHING);

        _window = SDL_CreateWindow("Afeb", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
        if (_window == nullptr) {
            fatalError("SDL Window could not be created!");
        }

        // OpenGL initialization logic
        SDL_GLContext glContext = SDL_GL_CreateContext(_window);
        if (glContext == nullptr) {
            fatalError("SDL_GL context could not be created!");
        }

        GLenum error = glewInit();
        if (error != GLEW_OK) {
            fatalError("Could not initialize glew!");
        }

        // set up two buffers
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0);
        initShaders();

        // Set up Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        // Set up Dear ImGui style
        ImGui::StyleColorsDark();

        // Set up platform/renderer bindings
        ImGui_ImplSDL2_InitForOpenGL(_window, glContext);
        ImGui_ImplOpenGL3_Init();

    }

    void MainWindow::mainLoop() {

        while (_windowState != WindowState::OFF) {
            processInput();

            // Set up Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame(_window);
            ImGui::NewFrame();

            ImGui::Text("Hello, world!");

            drawWindow();


        }
    }

    void MainWindow::processInput() {
        SDL_Event evnt;

        // Forward events to Dear ImGui
        while (SDL_PollEvent(&evnt)) {
            ImGui_ImplSDL2_ProcessEvent(&evnt);
            if (evnt.type == SDL_QUIT ||
                (evnt.type == SDL_WINDOWEVENT
                    && evnt.window.event == SDL_WINDOWEVENT_CLOSE
                    && evnt.window.windowID == SDL_GetWindowID(_window))) {
                _windowState = WindowState::OFF;
            }
        }
        /*
        while (SDL_PollEvent(&evnt)) {
            switch (evnt.type) {
            case SDL_QUIT:
                _windowState = WindowState::OFF;
                break;
            case SDL_MOUSEBUTTONDOWN:
                std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
                _pt1 = glm::vec3(evnt.motion.x/1224.0, evnt.motion.y/868.0, 0.0);
            }
        }
         */
    }

    void MainWindow::drawWindow() {
        // Set the base depth to 1.0
        glClearDepth(1.0);
        // Clear the color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Shaders
        _shaderProgram.use();

        glLineWidth(cst::OPENGL_LINE_WIDTH);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glm::vec3 positions[cst::TRIANGLE_POINTS] = {
            glm::vec3(-0.5f, -0.5f, 0.0f),
            glm::vec3(0.0f, 0.5f, 0.0f),
            glm::vec3(0.5f, -0.5f, 0.0f)};
        glm::vec3 color(1.0f, 0.0f, 0.0f);
        Triangle triangle(positions, &color);

        // transformation matrix
        glm::mat4 m(1.0f);

        //m = glm::translate(m, glm::vec3(0.5f, 0.5f, 0.0f));
        //m = glm::rotate(m, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        m = glm::scale(m, glm::vec3(0.5f, 0.5f, 0.0f));
        triangle.transform(m);
        triangle.draw();

        _coordSystem.draw();

        _shaderProgram.unuse();

        // Render Dear ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers and draw everything to the screen
        SDL_GL_SwapWindow(_window);
    }

    void MainWindow::initShaders() {
        _shaderProgram.compileShaders("./shaders/basic.vert", "./shaders/basic.frag");
        _shaderProgram.linkShaders();
    }

} // namespace Afeb
