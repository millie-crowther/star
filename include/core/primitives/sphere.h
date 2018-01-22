#ifndef SPHERE_PRIMITIVE_H
#define SPHERE_PRIMITIVE_H

#include "core/primitive.h"

namespace primitives {
    class sphere_t : public primitive_t {
        double distance(glm::vec3 v){
            return glm::length(v) - 0.7;
	}
    };
}

#endif
