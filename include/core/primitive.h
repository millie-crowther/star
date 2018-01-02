#ifndef PRIMITIVE_H
#define PRIMITIVW_H

#include <glm/glm.hpp>

class primitive_t {
public:
    // pure virtual functions
    virtual double distance(glm::vec3 v) = 0;

    // virtual functions
    virtual glm::vec3 normal(glm::vec3 v);
};

#endif
