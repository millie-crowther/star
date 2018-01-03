#include "core/bounds.h"

bounds_t::bounds_t(glm::vec3 c, double s){
    centre = c;
    size = s;
}

bounds_t
bounds_t::bounds_for_octant(int i){
    double s = size / 2.0f;

    int dx = (i & 1) * 2 - 1;
    int dy = (i & 2) - 1;
    int dz = (i & 4) / 2 - 1;

    glm::vec3 c = centre + ((float)size) * glm::vec3(dx, dy, dz) / 4.0f; 

    return bounds_t(c, s); 
}
