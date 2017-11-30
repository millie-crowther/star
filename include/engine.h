#ifndef STAR_ENGINE_H
#define STAR_ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class engine_t {
private:
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
    GLFWwindow * window;

    void draw();
    void update(double delta);

public:
    bool initialise();
    void run();
    void terminate();
};

#endif
