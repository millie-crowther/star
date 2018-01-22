#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "bounds.h"
#include "rendering/material.h"

/*
 *  abstract class
 */ 
class primitive_t {
protected:
    // singleton variables
    static material_t default_material = material_t(glm::vec3(0.7, 0.3, 0.7))

public:
    // abstract functions
    virtual double distance(glm::vec3 v) = 0;

    // virtual functions
    virtual bool surface_intersects(bounds_t bounds);
    virtual material_t * get_material();
    virtual bounds_t get_upper_bound();
};

#endif
