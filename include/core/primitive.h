#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "bounds.h"
#include "rendering/material.h"

/*
 *  abstract class
 */ 
class primitive_t {
protected:
    // virtual functions
    virtual bool is_convex();
    virtual bool contains(glm::vec3 v);
    
    // non-virtual functions
    bool is_on_surface(glm::vec3 v);

public:
    // abstract functions
    virtual double distance(glm::vec3 v) = 0;

    // virtual functions
    virtual glm::vec3 normal(glm::vec3 v);
    virtual bool surface_intersects(bounds_t bounds);
    virtual material_t * get_material_at(bounds_t bounds);
    virtual bounds_t get_upper_bound();
};

#endif
