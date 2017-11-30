#include "engine.h"
#include <iostream>

static void 
key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

bool 
engine_t::initialise(){
    if (!glfwInit()){
        std::cout << "Failed to initialise GLFW" << std::endl;
        return false;
    }

    window = glfwCreateWindow(640, 480, "hello world!", nullptr, nullptr);
    if (window == nullptr){
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    return true;
}

void
engine_t::terminate(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void
engine_t::draw(){
    glClear(GL_COLOR_BUFFER_BIT);
}

void
engine_t::update(double delta){
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void
engine_t::run(){
    while (!glfwWindowShouldClose(window)){
        draw();
        update(0.0);
    }
}
