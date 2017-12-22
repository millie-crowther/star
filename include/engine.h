#ifndef STAR_ENGINE_H
#define STAR_ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include "input.h"
#include "rendering/renderer.h"

class engine_t {
private:
    GLFWwindow * window;

    double theta;

    input_t input;
    renderer_t renderer;

    void update(double delta);

public:
    bool initialise();
    void run();
    void terminate();
};

#endif
