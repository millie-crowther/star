#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "rendering/ssbo_data.h"
#include "rendering/camera.h"

class renderer_t {
private:
    camera_t * main_camera;
    GLFWwindow * window;
    GLint program;
    int width;
    int height;

    //private helper methods
    void update_ssbo_data(ssbo_data_t * data, int n);    

public:
    // constructors and destructors
    renderer_t();

    // setters
    void set_main_camera(camera_t * camera);
    

    //public methods
    bool initialise(GLFWwindow * window);
    void draw();
    void update_window_size(int width, int height);
};

#endif
