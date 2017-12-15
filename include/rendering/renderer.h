#ifndef RENDERER_H
#define RENDERER_H

#include "rendering/camera.h"
#include <GLFW/glfw3.h>

class renderer_t {
private:
    camera_t * main_camera;
    GLFWwindow * window;

public:
    // constructors and destructors
    renderer_t(GLFWwindow * window);

    // setters
    void set_main_camera(camera_t * camera);
};

#endif
