#include "rendering/render_octree.h"

#include <algorithm>

render_octree_t::render_octree_t(renderer_t * r, render_octree_t * p, material_t * m){
    renderer = r;
    parent   = p;
    children = nullptr;
    material = m;
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
    return std::all_of(children.begin(), children.end(), [](render_octree_t * t) { return t == nullptr });
}

int
render_octree_t::get_material_id(material_t * material, std::vector<material_t> * materials){
    // TODO: remove duplicates
    materials->push_back(material);
    return materials->size() - 1;        
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
render_octree_t::subdivide(){
    kill_children();
    children.fill(new render_octree_t(renderer, this, nullptr));
}

void 
render_octree_t::kill_children(){
    std::foreach(children.begin(), children.end(), [](render_octree_t * t){ if (t != nullptr) delete t; });
    children.fill(nullptr);
}

void
render_octree_t::merge_children(){
    if (!is_leaf() && has_homogenous_children()){
        material_t * m = children[0].material;
        kill_children();
        set_material(m);
    }
}

void
render_octree_t::set_material(material_t * material){
    this->material = material;

    if (!is_root()){
        parent->merge_children();
    }    
}

void
render_octree_t::paint(bounds_t bounds, primitive_t * primitive){
    if (renderer->is_visible(bounds) && primitive->surface_intersects(bounds)){
        if (renderer->is_terminal(bounds)){
            set_material(primitive->get_material());            
 
	} else {
            if (is_leaf()){
                subdivide();          
            }

	    for (int i = 0; i < 8; i++){
                children[i].paint(bounds.bounds_for_octant(i), primitive);
	    }
	}
    }
}
