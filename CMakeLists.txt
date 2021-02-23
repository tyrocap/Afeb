cmake_minimum_required(VERSION 3.17)
project(Afeb)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(include
        imgui/
        imgui/backends/)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Freetype REQUIRED)

add_library(imgui STATIC
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/backends/imgui_impl_sdl.cpp
        imgui/backends/imgui_impl_opengl3.cpp)
target_include_directories(imgui PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(imgui PUBLIC imgui/ imgui/backends/)
target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_CUSTOM=<SDL_opengl.h> GL_GLEXT_PROTOTYPES=1)

add_executable(Afeb main.cpp src/MainWindow.cpp include/MainWindow.h src/CoordSystem.cpp include/CoordSystem.h src/GlslProgram.cpp include/GlslProgram.h include/Error.h src/Error.cpp src/Triangle.cpp include/Triangle.h src/Camera3D.cpp include/Camera3D.h)

target_include_directories(Afeb PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(Afeb PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(Afeb PUBLIC ${GLEW_INCLUDE_DIRS})
target_include_directories(Afeb PUBLIC ${FREETYPE_INCLUDE_DIRS})

target_link_libraries(Afeb PUBLIC ${OPENGL_LIBRARIES})
target_link_libraries(Afeb PUBLIC ${SDL2_LIBRARIES})
target_link_libraries(Afeb PUBLIC ${GLEW_LIBRARIES})
target_link_libraries(Afeb PUBLIC ${FREETYPE_LIBRARIES})
target_link_libraries(Afeb PUBLIC imgui)
