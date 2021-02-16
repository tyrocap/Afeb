cmake_minimum_required(VERSION 3.17)
project(Afeb)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(include)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Freetype REQUIRED)

add_executable(Afeb main.cpp src/MainWindow.cpp include/MainWindow.h src/CoordSystem.cpp include/CoordSystem.h src/GLSLProgram.cpp include/GLSLProgram.h include/Error.h src/Error.cpp src/Triangle.cpp include/Triangle.h)

target_include_directories(Afeb PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(Afeb PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(Afeb PUBLIC ${GLEW_INCLUDE_DIRS})
target_include_directories(Afeb PUBLIC ${FREETYPE_INCLUDE_DIRS})

target_link_libraries(Afeb PUBLIC ${OPENGL_LIBRARIES})
target_link_libraries(Afeb PUBLIC ${SDL2_LIBRARIES})
target_link_libraries(Afeb PUBLIC ${GLEW_LIBRARIES})
target_link_libraries(Afeb PUBLIC ${FREETYPE_LIBRARIES})
