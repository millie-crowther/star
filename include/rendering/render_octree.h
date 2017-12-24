#ifndef RENDER_OCTREE_H
#define RENDER_OCTREE_H

#include "material.h"

class render_octree_t {
private:
    render_octree_t * parent;
    render_octree_t * children;
    material_t * material;

public:
    //cconstructors and destructors
    render_octree_t(render_octree_t * parent, material_t * material);
    ~render_octree_t();
};

#endif
