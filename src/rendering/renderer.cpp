#include "rendering/renderer.h"

renderer_t::renderer_t(GLFWwindow * window){
    main_camera = nullptr;
    this->window = window;
}

void
set_main_camera(camera_t * camera){
    main_camera = camera; 
}
