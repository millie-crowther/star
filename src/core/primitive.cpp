#include "core/primitive.h"

#include <algorithm>
#include "utils/maths.h"

bool
primitive_t::is_convex(){
    return false;
}

bool
primitive_t::contains(glm::vec3 v){
    return distance(v) <= 0.0;
}

bool 
primitive_t::is_on_surface(glm::vec3 v){
    return maths::approx(distance(v), 0.0);
}

bool
primitive_t::surface_intersects(bounds_t bounds){
    // check corners
    auto corners = bounds.get_corners();
    int count = std::count_if(corners.begin(), corners.end(), [this](glm::vec3 v){
        return this->contains(v);
    });

    if (count > 0 && count < 8){
	return true;
    }

    // if convex and interior, thats all we need to do
    if (is_convex() && count == 8){
	return false;
    }
    
    double d = abs(distance(bounds.centre));
	
    // upper bound check
    if (d >= glm::length(glm::vec3(bounds.size / 2.0))){
        return false;
    }

    // lower bound check (redundant for now)
    /*
    if (d <= bounds.size / 2.0){
        return true;
    }
    // */

    // ideas:
    // 1) go through corners and check them
    // 2) at this point, surface types left are:
    //    (a) concave surface which hits every corner
    //    (b) surface which hasnt hit any corner but closest point lies 
    //        somewhere in ambiguous region

    // this function may return false positives as-is.
    // TODO: analyse performace trade-off between:
    //       1) putting in more CPU time here to determine exact solution
    //       2) just returning true and catching correct result deeper in tree
    return true; 
}
