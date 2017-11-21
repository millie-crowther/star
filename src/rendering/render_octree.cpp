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
