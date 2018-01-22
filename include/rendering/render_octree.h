#ifndef RENDER_OCTREE_H
#define RENDER_OCTREE_H

#include "renderer.h"
#include "core/primitive.h"
#include "material.h"
#include <vector>
#include <array>

class render_octree_t {
private:
    renderer_t * renderer;
    render_octree_t * parent;
    std::array<render_octree_t *, 8> children;
    material_t * material;

    bool is_root();
    bool is_leaf();

    void kill_children();
    bool has_homogenous_children();
    void merge_children();
    void subdivide();

    void set_material(material_t * material);
    
    int get_material_id(material_t * material, std::vector<material_t> * materials);
    void flatten_helper(int * ptr, std::vector<int> * structure, std::vector<material_t> * mats);

public:
    // constructors and destructors
    render_octree_t(renderer_t * renderer, render_octree_t * parent, material_t * material);
    ~render_octree_t();

    // public methods
    void flatten(std::vector<int> * structure, std::vector<material_t> * materials);
    void paint(bounds_t bounds, primitive_t * primitive);
};

#endif
