#include "input.h"

#include <map>
#include <iostream>

std::map<GLFWwindow *, input_t *> inputs;

/*
 *  callbacks
 */

static void
key_callback(GLFWwindow * window, int key, int scancode, int action, int mods){
    if (inputs.find(window) != inputs.end()){
       if (action == GLFW_PRESS || action == GLFW_RELEASE){ 
           inputs[window]->key_event(key, action == GLFW_PRESS);
       }
    }    
}

static void
mouse_button_callback(GLFWwindow * window, int button, int action, int mods){
    if (inputs.find(window) != inputs.end()){
        if (action == GLFW_PRESS || action == GLFW_RELEASE){
            inputs[window]->mouse_button_event(button, action == GLFW_PRESS);
        }
    }
}

static void 
cursor_pos_callback(GLFWwindow * window, double x, double y){
    if (inputs.find(window) != inputs.end()){
        inputs[window]->mouse_pos_update(x, y);
    }
}

bool
input_t::is_valid_key(int keycode){
    return keycode >= 0 && keycode <= GLFW_KEY_LAST;
}

bool
input_t::is_valid_mouse_button(int button){
    return button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST;
}

input_t::input_t(){
    this->window = nullptr;

    for (int key = 0; is_valid_key(key); key++){
        keys[key] = false;
    }

    for (int button = 0; is_valid_mouse_button(button); button++){
        mouse[button] = false;
    }
}

input_t::~input_t(){
    for (auto it = inputs.begin(); it != inputs.end();){
        if ((it->second) == this){
            it = inputs.erase(it);
        } else {
            it++;
        }
    }
}

void
input_t::set_window(GLFWwindow * window){
    this->window = window;
    
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    
    inputs.emplace(window, this);
}

void
input_t::key_event(int keycode, bool isPress){
    if (is_valid_key(keycode)){
        keys[keycode] = isPress;
    }
}

void
input_t::mouse_button_event(int button, bool isPress){
    if (is_valid_mouse_button(button)){
        mouse[button] = isPress;
    }
}

void 
input_t::mouse_pos_update(double x, double y){
    double now = glfwGetTime();
    glm::vec2 new_pos(x, y);
    
    mouse_v = (new_pos - mouse_p) / (float)(now - last_mouse_update);
    mouse_p = new_pos;

    last_mouse_update = now;
}

glm::vec2
input_t::get_mouse_pos(){
    if (window == nullptr){
        return glm::vec2();
    }
    
    return mouse_p;
}

glm::vec2
input_t::get_mouse_velocity(){
    if (window == nullptr){
        return glm::vec2(0.0);
    }

    return mouse_v;
}

bool
input_t::is_key_pressed(int keycode){
    if (window == nullptr || !is_valid_key(keycode)){
	return false;
    }

    return keys[keycode];
}

bool 
input_t::is_mouse_button_pressed(int button){
   if (window == nullptr || !is_valid_mouse_button(button)){
       return false;
   }
   
   return mouse[button];
}
