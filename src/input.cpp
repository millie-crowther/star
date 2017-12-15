#include "input.h"

#include <set>
#include <map>
#include <iostream>

// TODO: is there really no nicer way to do this???
// TODO: check for concurrency issues when deleting from a collection
//       while another thread is iterating over it
// data has to be stored with respect to GLFWwindows because C is shit
std::set<GLFWwindow *> keys[GLFW_KEY_LAST + 1];
std::set<GLFWwindow *> mouse_buttons[GLFW_MOUSE_BUTTON_LAST + 1];
std::map<GLFWwindow *, double> cursor_x;
std::map<GLFWwindow *, double> cursor_y;
std::map<GLFWwindow *, double> cursor_dx;
std::map<GLFWwindow *, double> cursor_dy;
std::map<GLFWwindow *, double> last_cursor_update;

/*
 *  callbacks
 */

static void
key_callback(GLFWwindow * window, int key, int scancode, int action, int mods){
    if (key >= 0 && key <= GLFW_KEY_LAST){   
       	if (action == GLFW_PRESS){
            keys[key].insert(window);
        }

        if (action == GLFW_RELEASE){
            keys[key].erase(window);
        }
    }
}

static void
mouse_button_callback(GLFWwindow * window, int button, int action, int mods){
   if (button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST){
       if (action == GLFW_PRESS){
          mouse_buttons[button].insert(window);
       }

       if (action == GLFW_RELEASE){
           mouse_buttons[button].erase(window);
       }
   }
}

static void 
cursor_pos_callback(GLFWwindow * window, double x, double y){
    double now = glfwGetTime();

    cursor_dx[window] = (x - cursor_x[window]) / (now - last_cursor_update[window]);  
    cursor_dy[window] = (y - cursor_y[window]) / (now - last_cursor_update[window]);
    cursor_x[window] = x;
    cursor_y[window] = y;
    last_cursor_update[window] = now;
}

input_t::input_t(GLFWwindow * window){
    this->window = window;
    last_cursor_update[window] = glfwGetTime();

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
}

input_t::~input_t(){
    for (int key = 0; key <= GLFW_KEY_LAST; key++){
	keys[key].erase(window);
    }

    for (int btn = 0; btn <= GLFW_MOUSE_BUTTON_LAST; btn++){
        mouse_buttons[btn].erase(window);
    }

    cursor_x.erase(window);
    cursor_y.erase(window);
    cursor_dx.erase(window);
    cursor_dy.erase(window);
    last_cursor_update.erase(window);
}

glm::vec2
input_t::get_mouse_pos(){
    return glm::vec2(cursor_x[window], cursor_y[window]);
}

glm::vec2
input_t::get_mouse_velocity(){
    return glm::vec2(cursor_dx[window], cursor_dy[window]);
}

bool
input_t::is_key_pressed(int keycode){
    if (keycode < 0 || keycode > GLFW_KEY_LAST){
	return false;
    }

    return keys[keycode].find(window) != keys[keycode].end();
}


