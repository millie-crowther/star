#ifndef STAR_ENGINE_H
#define STAR_ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class engine_t {
private:
    GLuint program;
    GLFWwindow * window;
   
    std::string get_fragment_shader();

    void draw();
    void update(double delta);

public:
    bool initialise();
    void run();
    void terminate();

    void update_window_size(int width, int height);
};

#endif
