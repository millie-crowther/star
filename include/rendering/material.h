#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

class material_t {
private:
    glm::vec3 colour;
    float albedo;

public:
    material_t(glm::vec3 c, float a){
        colour = c;
        albedo = a;
    }

    bool is_similar(material_t * other, float threshold){
        if (glm::length(colour - other->colour) > threshold){
            return false;
        }

        if (abs(albedo - other->albedo) > threshold){
            return false;
        }

        return true;
    }
};

#endif
