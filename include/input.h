#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class input_t {
private:
    GLFWwindow * window;

    bool keys[GLFW_KEY_LAST + 1];
    bool mouse[GLFW_MOUSE_BUTTON_LAST + 1];
    
    glm::vec2 mouse_p;
    glm::vec2 mouse_v;
    double last_mouse_update;

    //static functions
    static bool is_valid_key(int keycode);
    static bool is_valid_mouse_button(int button);

public:
    // constructors and destructors
    input_t();
    ~input_t();

    //functions called on event
    void key_event(int keycode, bool isPress);
    void mouse_button_event(int button, bool isPress);
    void mouse_pos_update(double x, double y);

    //setters
    void set_window(GLFWwindow * window);

    //getters
    glm::vec2 get_mouse_pos();
    glm::vec2 get_mouse_velocity();

    bool is_key_pressed(int keycode);
    bool is_mouse_button_pressed(int button);
};

#endif
