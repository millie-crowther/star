#ifndef BOUNDS_H
#define BOUNDS_H

#include <glm/glm.hpp>

class bounds_t {
public:
    glm::vec3 centre;
    glm::vec3 size;
    
    // constructors and destructors
    bounds_t(glm::vec3 c, glm::vec3 s);

    // public methods
    bounds_t bounds_for_octant(int octant);
};

#endif
