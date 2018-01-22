#include "core/engine.h"
#include <iostream>
#include "rendering/render_octree.h"
#include "core/primitives.h"
#include "core/bounds.h"

int main(){
    renderer_t r;
    render_octree_t o(&r, nullptr);
    primitives::sphere_t s;
    o.paint(bounds_t(glm::vec3(0), 4), &s);
    std::vector<int> st;
    std::vector<material_t> m;
    o.flatten(&st, &m);

    for (int i : st){
        std::cout << i << ", ";
    }

    std::cout << std::endl;

    std::cout << "size: " << st.size() << std::endl;

    engine_t engine;
    
    if (!engine.initialise()){
        std::cout << "Engine failed to initialise. Aborting." << std::endl;
        return 1;
    }

    engine.run();

    engine.terminate();
    return 0;
}
