cmake_minimum_required(VERSION 3.0)

project(terrain)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


SET(SOURCE_FILES
    src/main.cpp
    src/window.cpp
    src/utils.cpp
    src/shader.cpp
    src/triangle.cpp
    src/camera.cpp
    src/linear_interpolator.cpp
    src/terrain.cpp
    src/terrain_height_map.cpp
    src/fractal_terrain_generator.cpp
    )



add_executable(terrain ${SOURCE_FILES})

include_directories(include)
target_link_libraries(terrain sfml-graphics sfml-window sfml-system GL glut GLEW dl)
