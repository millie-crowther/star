#include "rendering/renderer.h"

renderer_t::renderer_t(){
    main_camera = nullptr;
    window = nullptr;
}

void
renderer_t::set_main_camera(camera_t * camera){
    main_camera = camera; 
}

void 
renderer_t::set_window(GLFWwindow * window){
    this->window = window;
}
