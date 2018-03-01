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

    ../include/core/engine.h
    ../src/core/engine.cpp

    ../include/rendering/material.h
    ../src/rendering/material.cpp

    ../include/utils/resources.h
    ../include/utils/maths.h

    ../include/input.h
    ../src/input.cpp

    ../include/scene/transform.h
    ../src/scene/transform.cpp

    ../include/rendering/renderer.h
    ../src/rendering/renderer.cpp

    ../include/rendering/camera.h
    ../src/rendering/camera.cpp

    ../include/core/primitive.h
    ../src/core/primitive.cpp

    ../include/core/primitives.h
    ../include/core/primitives/sphere.h

    ../include/core/bounds.h
    ../src/core/bounds.cpp

    gladbuild/src/glad.c 
)

find_package(OpenGL REQUIRED)

add_executable(star ${SOURCES})
target_link_libraries(star glfw)

