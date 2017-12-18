#ifndef RENDERER_H
#define RENDERER_H

#include "rendering/camera.h"
#include <GLFW/glfw3.h>

class renderer_t {
private:
    camera_t * main_camera;
    GLFWwindow * window;
    GLint program;

public:
    // constructors and destructors
    renderer_t();

    // setters
    void set_main_camera(camera_t * camera);
    void set_window(GLFWwindow * window);

    //public methods
    void draw();
};

#endif
