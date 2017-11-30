#ifndef STAR_ENGINE_H
#define STAR_ENGINE_H

#include <GLFW/glfw3.h>

class engine_t {
private:
    GLFWwindow * window;

    void draw();
    void update(double delta);

public:
    bool initialise();
    void run();
    void terminate();
};

#endif
