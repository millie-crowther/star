#include "scene/transform.h"

glm::vec3
transform_t::get_forward(){
    return glm::vec3(0.0, 0.0, 1.0);
}

glm::vec3
transform_t::get_right(){
    return glm::vec3(1.0, 0.0, 0.0);
}

void
transform_t::add_child(transform_t * child){
    child->parent = this;
}
