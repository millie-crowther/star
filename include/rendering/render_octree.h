#ifndef RENDER_OCTREE_H
#define RENDER_OCTREE_H

#include "core/primitive.h"
#include "material.h"
#include <vector>

class render_octree_t {
private:
    render_octree_t * parent;
    render_octree_t * children;
    material_t * material;

    bool is_leaf();
    bool is_terminal();

    int get_material_id(material_t * material, std::vector<material_t> * materials);
    void flatten_helper(int * ptr, std::vector<int> * structure, std::vector<material_t> * mats);

public:
    // constructors and destructors
    render_octree_t(render_octree_t * parent, material_t * material);
    ~render_octree_t();

    // public methods
    void flatten(std::vector<int> * structure, std::vector<material_t> * materials);
    void paint(bounds_t bounds, primitive_t * primitive);
};

#endif
