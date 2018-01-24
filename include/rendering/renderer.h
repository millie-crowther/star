#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "rendering/camera.h"
#include "core/bounds.h"
#include <vector>

class renderer_t {
private:
    camera_t * main_camera;
    GLFWwindow * window;
    GLint program;
    int width;
    int height;
    GLuint octree_ssbo;

    bounds_t get_global_bounds();
    void upload_octree_data(std::vector<int> * data);

public:
    // constructors and destructors
    renderer_t();

    // setters
    void set_main_camera(camera_t * camera);

    //public methods
    bool initialise(GLFWwindow * window);
    void draw();
    void update_window_size(int width, int height);

    bool is_visible(bounds_t bounds);
    bool is_terminal(bounds_t bounds);
};

#endif
