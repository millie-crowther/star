#include "rendering/render_octree.h"

#include <iostream>
#include <algorithm>

render_octree_t::render_octree_t(renderer_t * r, render_octree_t * p){
    renderer = r;
    parent   = p;
    children = nullptr;
    material = nullptr;
}

render_octree_t::~render_octree_t(){
    kill_children();
}

bool
render_octree_t::is_root(){
    return parent == nullptr;
}

bool
render_octree_t::is_leaf(){
    return children == nullptr;
}

bool
render_octree_t::has_homogenous_children(){
    // TODO
    return false;
}

void 
render_octree_t::flatten_helper(int * ptr, std::vector<int> * structure){
    // go back and set your parents pointer to you
    *ptr = structure->size();

    if (is_leaf()){
        // set material id
        // negative to distinguish from branch nodes
        structure->push_back(material == nullptr ? 0 : -1);
    
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
            children->at(i).flatten_helper(&structure->at(start + i), structure);
        }
    }
}

void
render_octree_t::flatten(std::vector<int> * structure){
    if (structure != nullptr){
        int dummy;
        flatten_helper(&dummy, structure);
    } 
}

void 
render_octree_t::subdivide(){
    kill_children();
    children = new std::vector<render_octree_t>(8, render_octree_t(renderer, this));
}

void 
render_octree_t::kill_children(){
    delete children;
    children = nullptr;
}

void
render_octree_t::merge_children(){
    if (!is_leaf() && has_homogenous_children()){
        set_material(children->at(0).material);
        kill_children();

	if (!is_root()){
            parent->merge_children();
	}
    }
}

void
render_octree_t::set_material(material_t * material){
    this->material = material;
}

void
render_octree_t::paint(bounds_t bounds, primitive_t * primitive){
    if (primitive->surface_intersects(bounds)){
        if (renderer->is_terminal(bounds)){
            set_material(primitive->get_material());            
 
	} else {
            if (is_leaf()){
                subdivide();          
            }

	    for (int i = 0; i < 8; i++){
                children->at(i).paint(bounds.bounds_for_octant(i), primitive);
	    }
	}
    }
}
