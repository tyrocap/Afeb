//
// Created by adam on 2/14/21.
//

#include "../include/MainWindow.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include "Camera3D.h"
#include "Error.h"



namespace Afeb {

    namespace cst {
        const int SCREEN_WIDTH = 1224;
        const int SCREEN_HEIGHT = 918;
        const int OPENGL_LINE_WIDTH = 4;
        const int COLOR_FLAG_INDEX = 0;
        const int TRANSLATE_FLAG_INDEX = 1;
        const int ROTATE_FLAG_INDEX = 2;
        const int SCALE_FLAG_INDEX = 3;
        const int DRAW_FILLED_FLAG_INDEX = 4;
    } // namespace cst

    MainWindow::MainWindow() : _window(nullptr),
                               _screenWidth(cst::SCREEN_WIDTH),
                               _screenHeight(cst::SCREEN_HEIGHT),
                               _windowState(WindowState::ON),
                               _color(glm::vec3()),
                               _translate(glm::vec3()),
                               _rotate(0.0f),
                               _scale(glm::vec3()),
                               _camera(){};

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
        ImGuiIO& io = ImGui::GetIO();
        (void)io;

        // Set up Dear ImGui style
        ImGui::StyleColorsDark();

        // Set up platform/renderer bindings
        ImGui_ImplSDL2_InitForOpenGL(_window, glContext);
        ImGui_ImplOpenGL3_Init();

        // Camera
        _camera.setPosition(glm::vec3(0, 0, 2));
        _camera.setViewportAspectRatio((float)cst::SCREEN_WIDTH / cst::SCREEN_HEIGHT);
    }

    void MainWindow::mainLoop() {

        while (_windowState != WindowState::OFF) {
            processInput();

            // Set up Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame(_window);
            ImGui::NewFrame();

            // From ImGui Demo Code
            static ImVec4 color = ImVec4(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f);

            static ImGuiColorEditFlags misc_flags = ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoOptions;

            ImGui::Text("Color picker:");
            static bool ref_color = false;
            static ImVec4 ref_color_v(0.0f, 0.0f, 0.0f, 1.0f);
            static int display_mode = 0;
            static int picker_mode = 0;

            ImGui::Combo("Display Mode", &display_mode, "Auto/Current\0None\0RGB Only\0HSV Only\0Hex Only\0");
            ImGuiColorEditFlags flags = misc_flags;

            if (picker_mode == 1)
                flags |= ImGuiColorEditFlags_PickerHueBar;
            if (picker_mode == 2)
                flags |= ImGuiColorEditFlags_PickerHueWheel;
            if (display_mode == 1)
                flags |= ImGuiColorEditFlags_NoInputs; // Disable all RGB/HSV/Hex displays
            if (display_mode == 2)
                flags |= ImGuiColorEditFlags_DisplayRGB; // Override display mode
            if (display_mode == 3)
                flags |= ImGuiColorEditFlags_DisplayHSV;
            if (display_mode == 4)
                flags |= ImGuiColorEditFlags_DisplayHex;
            ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, ref_color ? &ref_color_v.x : NULL);
            // End

            // Copy the changed color to member variable so
            // it can used in drawWindow() to change
            // color of a drawn object in the loop
            if (_color.x != color.x || _color.y != color.y || _color.z != color.z) {
                _color = glm::vec3(color.x, color.y, color.z);
                _flags[cst::COLOR_FLAG_INDEX] = true;
            }

            // Translate
            static float translate[3] = {0.0f, 0.0f, 0.0f};
            ImGui::SliderFloat3("translate", translate, -1.0f, 1.0f);
            if (_translate.x != translate[0] || _translate.y != translate[1] || _translate.z != translate[2]) {
                _translate = glm::vec3(translate[0], translate[1], translate[2]);
                _flags[cst::TRANSLATE_FLAG_INDEX] = true;
            }

            // Rotate
            static float rotate = 0.0f;
            ImGui::SliderFloat("rotate", &rotate, 0.0f, 360.0f);
            if (_rotate != rotate) {
                _rotate = rotate;
                _flags[cst::ROTATE_FLAG_INDEX] = true;
            }

            // Scale
            static float scale[3] = {1.0f, 1.0f, 1.0f};
            ImGui::SliderFloat3("scale", scale, -1.0f, 1.0f);
            if (_scale.x != scale[0] || _scale.y != scale[1] || _scale.z != scale[2]) {
                _scale = glm::vec3(scale[0], scale[1], scale[2]);
                _flags[cst::SCALE_FLAG_INDEX] = true;
            }

            // Draw Filled
            static bool drawFilled = false;
            ImGui::Checkbox("Draw Filled", &drawFilled);
            if (_flags[cst::DRAW_FILLED_FLAG_INDEX] != drawFilled) {
                _flags[cst::DRAW_FILLED_FLAG_INDEX] = drawFilled;
            }

            drawWindow();
        }
    }

    void MainWindow::processInput() {
        SDL_Event evnt;
        const float moveSpeed = 0.01f;

        // Forward events to Dear ImGui
        while (SDL_PollEvent(&evnt)) {
            ImGui_ImplSDL2_ProcessEvent(&evnt);
            ImGuiIO& io = ImGui::GetIO();
            if (!io.WantCaptureMouse) {
                switch (evnt.type) {
                case SDL_QUIT:
                    _windowState = WindowState::OFF;
                    break;
                case SDL_KEYDOWN:
                    switch (evnt.key.keysym.sym) {
                    case SDLK_UP:
                        _camera.offsetPosition(moveSpeed * _camera.forward());
                        break;
                    case SDLK_DOWN:
                        _camera.offsetPosition(moveSpeed * -_camera.forward());
                        break;
                    case SDLK_LEFT:
                        _camera.offsetPosition(moveSpeed * -_camera.right());
                        break;
                    case SDLK_RIGHT:
                        _camera.offsetPosition(moveSpeed * _camera.right());
                        break;
                    case SDLK_x:
                        _camera.offsetPosition(moveSpeed * _camera.up());
                        break;
                    case SDLK_c:
                        _camera.offsetPosition(moveSpeed * -_camera.up());
                        break;
                    default:
                        break;
                    }
                case SDL_MOUSEBUTTONUP:
                    if (evnt.button.button == SDL_BUTTON_LEFT) {
                        SDL_SetRelativeMouseMode(SDL_FALSE);
                        _leftMousePressed = false;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (evnt.button.button == SDL_BUTTON_LEFT) {
                        _leftMousePressed = true;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (_leftMousePressed) {
                        SDL_SetRelativeMouseMode(SDL_TRUE);
                        auto offsetX = (float)evnt.motion.xrel;
                        auto offsetY = (float)evnt.motion.yrel;
                        _camera.processMouseMovement(offsetX, offsetY);
                        SDL_WarpMouseInWindow(_window, cst::SCREEN_WIDTH / 2, cst::SCREEN_HEIGHT / 2);
                    }
                case SDL_MOUSEWHEEL:
                    if (evnt.wheel.y == 1 || evnt.wheel.y == -1) {
                        _camera.processWheelMovement(evnt.wheel.y);
                    }
                default:
                    break;
                }
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

        glLineWidth(cst::OPENGL_LINE_WIDTH);
        if (_flags[cst::DRAW_FILLED_FLAG_INDEX]) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        glEnable(GL_DEPTH_TEST);

        std::string uniformCamera = "camera";
        std::string uniformModel = "model";
        glUniformMatrix4fv(glGetUniformLocation(_shaderProgram.getID(), uniformCamera.c_str()), 1,
            GL_FALSE, glm::value_ptr(_camera.matrix()));

        // triangle data
        glm::vec3 positions[cst::TRIANGLE_POINTS] = {
            glm::vec3(0.0f, 0.5f, 0.0f),
            glm::vec3(-0.5f, -0.5f, 0.5f),
            glm::vec3(0.5f, -0.5f, 0.5f)};
        glm::vec3 color(0.0f, 0.0f, 0.0f);

        glm::vec3 positions1[cst::TRIANGLE_POINTS] = {
            glm::vec3(0.0f, 0.5f, 0.0f),
            glm::vec3(0.5f, -0.5f, 0.5f),
            glm::vec3(0.5f, -0.5f, -0.5f)};
        glm::vec3 color1(0.0f, 1.0f, 0.5f);

        glm::vec3 positions2[cst::TRIANGLE_POINTS] = {
            glm::vec3(0.0f, 0.5f, 0.0f),
            glm::vec3(0.5f, -0.5f, -0.5f),
            glm::vec3(-0.5f, -0.5f, -0.5f)};
        glm::vec3 color2(1.0f, 0.0f, 0.0f);

        glm::vec3 positions3[cst::TRIANGLE_POINTS] = {
            glm::vec3(0.0f, 0.5f, 0.0f),
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3(-0.5f, -0.5f, 0.5f)};
        glm::vec3 color3(0.3f, 0.3f, 0.3f);

        Triangle triangle(positions, &color);
        Triangle triangle1(positions1, &color1);
        Triangle triangle2(positions2, &color2);
        Triangle triangle3(positions3, &color3);

        // transformation matrix
        glm::mat4 m(1.0f);

        if (_flags[cst::COLOR_FLAG_INDEX])
            triangle.changeColor(_color);
        if (_flags[cst::TRANSLATE_FLAG_INDEX])
            m = glm::translate(m, _translate);
        if (_flags[cst::ROTATE_FLAG_INDEX])
            m = glm::rotate(m, glm::radians(_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
        if (_flags[cst::SCALE_FLAG_INDEX])
            m = glm::scale(m, _scale);

        triangle.transform(m);
        triangle1.transform(m);
        triangle2.transform(m);
        triangle3.transform(m);

        triangle.draw();
        triangle1.draw();
        triangle2.draw();
        triangle3.draw();

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
