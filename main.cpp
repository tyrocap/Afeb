#include <iostream>
#include <SDL2/SDL.h>
#include <MainWindow.h>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"


int main(int argc, char* argv[]) {

    Afeb::MainWindow mainWindow;
    mainWindow.run();

    return 0;
}
