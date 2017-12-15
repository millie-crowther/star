#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

class transform_t {
private:

public:
    glm::vec3 get_forward();    
    glm::vec3 get_right();
};

#endif
