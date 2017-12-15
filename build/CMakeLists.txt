cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 11)
project (star)

set(PATH_TO_GLFW /home/millie/glfw)

add_subdirectory("glfw")

set(INCLUDE_DIR
    ../include
    gladbuild/include
)

include_directories(${INCLUDE_DIR})

set(SOURCES
    ../src/main.cpp

    ../include/engine.h
    ../src/engine.cpp

    ../include/rendering/render_octree.h
    ../src/rendering/render_octree.cpp

    ../include/rendering/material.h

    ../include/utils/resources.h
    ../src/utils/resources.cpp

    ../include/input.h
    ../src/input.cpp

    gladbuild/src/glad.c 
)

find_package(OpenGL REQUIRED)

add_executable(star ${SOURCES})
target_link_libraries(star glfw)

