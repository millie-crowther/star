#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

class transform_t {
private:
    transform_t * parent;

public:
    glm::vec3 get_forward();    
    glm::vec3 get_right();

    void add_child(transform_t * child);
};

#endif
