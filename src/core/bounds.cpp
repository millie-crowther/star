#include "core/bounds.h"

bounds_t::bounds_t(glm::vec3 c, glm::vec3 s){
    centre = c;
    size = s;
}

bounds_t
bounds_t::bounds_for_octant(int i){
    glm::vec3 s = size / 2.0f;

    int dx = (i & 1) * 2 - 1;
    int dy = (i & 2) - 1;
    int dz = (i & 4) / 2 - 1;

    glm::vec3 c = centre + size * glm::vec3(dx, dy, dz) / 4.0f; 

    return bounds_t(c, s); 
}
