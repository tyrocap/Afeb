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
        _color = glm::vec3(0.0f, 0.0f, 0.0f);
        _translate = glm::vec3(1.0f, 1.0f, 0.0f);
        _scale = glm::vec3(1.0f, 1.0f, 0.0f);
        _rotate = 0.0f;
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

            // From ImGui Demo Code
            static ImVec4 color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);

            static ImGuiColorEditFlags misc_flags = ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoOptions;

            ImGui::Text("Color picker:");
            static bool ref_color = false;
            static ImVec4 ref_color_v(1.0f, 0.0f, 1.0f, 0.5f);
            static int display_mode = 0;
            static int picker_mode = 0;

            ImGui::Combo("Display Mode", &display_mode, "Auto/Current\0None\0RGB Only\0HSV Only\0Hex Only\0");
            ImGuiColorEditFlags flags = misc_flags;

            if (picker_mode == 1)  flags |= ImGuiColorEditFlags_PickerHueBar;
            if (picker_mode == 2)  flags |= ImGuiColorEditFlags_PickerHueWheel;
            if (display_mode == 1) flags |= ImGuiColorEditFlags_NoInputs;       // Disable all RGB/HSV/Hex displays
            if (display_mode == 2) flags |= ImGuiColorEditFlags_DisplayRGB;     // Override display mode
            if (display_mode == 3) flags |= ImGuiColorEditFlags_DisplayHSV;
            if (display_mode == 4) flags |= ImGuiColorEditFlags_DisplayHex;
            ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, ref_color ? &ref_color_v.x : NULL);
            // End

            // Copy the changed color to member variable so
            // it can used in drawWindow() to change
            // color of a drawn object in the loop
            _color = glm::vec3(color.x, color.y, color.z);


            // Translate
            float translate[3];
            ImGui::SliderFloat3("translate", translate, 0.0f, 1.0f);
            _translate = glm::vec3(translate[0], translate[1], translate[2]);

            // Scale
            float scale[3];
            ImGui::SliderFloat3("scale", scale, 0.0f, 1.0f);
            _scale = glm::vec3(scale[0], scale[1], scale[2]);

            // Translate
            static float rotate;
            ImGui::SliderFloat("rotate", &rotate, 0.0f, 360.0f);
            _rotate = rotate;

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

        if (_translate.x > 0) {
            m = glm::translate(m, _translate);
        }
        if (_rotate > 0) {
            m = glm::rotate(m, glm::radians(_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        if (_scale.x > 0) {
            m = glm::scale(m, _scale);
        }
        triangle.transform(m);

        // TODO: Use a flag instead of value of a member variable
        // This is necessary because in this case, the value we
        // are checking against might be correct value in some
        // cases (e.g. user wants a color where 'R' = 0)
        if (_color.x > 0) {
            triangle.changeColor(_color);
        }
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
