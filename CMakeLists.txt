cmake_minimum_required(VERSION 3.17)
project(Afeb)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

add_executable(Afeb main.cpp src/MainWindow.cpp include/MainWindow.h)

target_include_directories(Afeb PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(Afeb PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(Afeb PUBLIC ${GLEW_INCLUDE_DIRS})

target_link_libraries(Afeb PUBLIC ${OPENGL_LIBRARIES})
target_link_libraries(Afeb PUBLIC ${SDL2_LIBRARIES})
target_link_libraries(Afeb PUBLIC ${GLEW_LIBRARIES})

