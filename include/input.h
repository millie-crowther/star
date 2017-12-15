#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class input_t {
private:
    GLFWwindow * window;

public:
    // constructors and destructors
    input_t(GLFWwindow * window);
    ~input_t();

    glm::vec2 get_mouse_pos();
    glm::vec2 get_mouse_velocity();

    bool is_key_pressed(int keycode);
};

#endif
