#ifndef RENDER_OCTREE_H
#define RENDER_OCTREE_H

#include "renderer.h"
#include "core/primitive.h"
#include "material.h"
#include <vector>

class render_octree_t {
private:
    renderer_t * renderer;
    render_octree_t * parent;
    std::vector<render_octree_t> * children;
    material_t * material;

    bool is_root();
    bool is_leaf();

    void kill_children();
    bool has_homogenous_children();
    void merge_children();
    void subdivide();

    void set_material(material_t * material);
    
    void flatten_helper(int * ptr, std::vector<int> * structure);

public:
    // constructors and destructors
    render_octree_t(renderer_t * renderer, render_octree_t * parent);
    ~render_octree_t();

    // public methods
    void flatten(std::vector<int> * structure);
    void paint(bounds_t bounds, primitive_t * primitive);
};

#endif
