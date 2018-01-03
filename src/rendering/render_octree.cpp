#include "rendering/render_octree.h"

render_octree_t::render_octree_t(render_octree_t * p, material_t * m){
    parent   = p;
    children = nullptr;
    material = m;
}

render_octree_t::~render_octree_t(){
    if (children != nullptr){
        delete children;
    }
}

bool
render_octree_t::is_leaf(){
    return children == nullptr;
}

int
render_octree_t::get_material_id(material_t * material, std::vector<material_t> * materials){
        
}

void 
render_octree_t::flatten_helper(
    int * ptr, 
    std::vector<int> * structure, 
    std::vector<material_t> * materials
){
    // go back and set your parents pointer to you
    *ptr = structure->size();

    if (is_leaf()){
        // set material id
        // negative to distinguish from branch nodes
        structure->push_back(-get_material_id(material, materials));
    
    } else {
        // allocate nodes for structure and recurse
        int start = structure->size();

        // put uninitialised pointers into array
        // TODO: first one is constant so can be ignored
        for (int i = 0; i < 8; i++){
            structure->push_back(0);
        }

        // recurse
        for (int i = 0; i < 8; i++){
            flatten_helper(&structure->at(start + i), structure, materials);
        }
    }
}

void
render_octree_t::flatten(std::vector<int> * structure, std::vector<material_t> * materials){
    if (structure != nullptr && materials != nullptr){
        int dummy;
        flatten_helper(&dummy, structure, materials);
    } 
}

void
render_octree_t::paint(bounds_t bounds, primitive_t * primitive){
    if (is_terminal()){
        material = primitive->get_material_at(bounds);

    } else if (primitive->surface_intersects(bounds)){
        for (int i = 0; i < 8; i++){
            children[i].paint(bounds.bounds_for_octant(i), primitive);
	}
    }
}

bool
render_octree_t::is_terminal(){
    //TODO: make more nodes terminal when they're further from the camera
    return is_leaf();
}
