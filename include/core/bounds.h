#ifndef BOUNDS_H
#define BOUNDS_H

#include <glm/glm.hpp>
#include <array>

class bounds_t {
public:
    glm::vec3 centre;
    double size;
    
    // constructors and destructors
    bounds_t(glm::vec3 c, double s);

    // public methods
    bounds_t bounds_for_octant(int octant);
    std::array<glm::vec3, 8> get_corners();
};

#endif
