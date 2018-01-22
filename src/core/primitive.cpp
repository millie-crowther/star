#include "core/primitive.h"

material_t default_material;

material_t * 
primitive_t::get_material(){
    return &default_material;
}

bounds_t 
primitive_t::get_upper_bound(){
    //TODO
    return bounds_t(glm::vec3(0), 1.0);
}

bool
primitive_t::surface_intersects(bounds_t bounds){
    // upper bound check
    double d = abs(distance(bounds.centre));
    if (d >= glm::length(glm::vec3(bounds.size / 2.0))){
        return false;
    }
   
    // by default return true and hope surface is caught further into tree 
    return true; 
}
