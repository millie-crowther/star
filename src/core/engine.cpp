#include "core/engine.h"
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "utils/resources.h"

static void
error_callback(int code, const char * description){
    std::cout << "GLFW encountered error " << code << ": " << description << std::endl;
}

bool 
engine_t::initialise(){
    glfwSetErrorCallback(error_callback);    

    if (!glfwInit()){
        std::cout << "Failed to initialise GLFW" << std::endl;
        return false;
    }

    int window_width = 160;
    int window_height = 120;

    window = glfwCreateWindow(window_width, window_height, "hello world!", nullptr, nullptr);
    if (window == nullptr){
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    input.set_window(window);    
    
    if (!renderer.initialise(window)){
        std::cout << "Failed to initialise renderer" << std::endl;
        glfwTerminate();
        return false;
    }
    
    return true;
}

void
engine_t::terminate(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void
engine_t::update(double delta){
    if (input.is_key_pressed(GLFW_KEY_ESCAPE)){ 
	glfwSetWindowShouldClose(window, GL_TRUE);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void
engine_t::run(){
    double time = glfwGetTime();
    while (!glfwWindowShouldClose(window)){
        double delta =  glfwGetTime() - time;
	time = glfwGetTime();
        
        double fps = 1.0 / delta;
	std::string title = "FPS: " + std::to_string(fps);
	glfwSetWindowTitle(window, title.c_str());

	update(delta);
	renderer.draw();
    }
}
