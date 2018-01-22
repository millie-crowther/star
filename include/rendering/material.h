#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include "utils/maths.h"

class material_t {
private:
    glm::vec3 colour;

public:
    // singleton variable
    static material_t default_mat = material_t(glm::vec3(0.7, 0.3, 0.7);

    // constructors and destructors
    material_t(glm::vec3 c);
};

#endif
