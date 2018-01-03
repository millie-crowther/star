#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "bounds.h"

class primitive_t {
protected:
    // virtual functions
    virtual bool is_convex();

public:
    // pure virtual functions
    virtual double distance(glm::vec3 v) = 0;

    // virtual functions
    virtual glm::vec3 normal(glm::vec3 v);
    virtual bool intersects(bounds_t bounds);
};

#endif
