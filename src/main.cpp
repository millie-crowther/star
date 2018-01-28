#include "core/engine.h"
#include <iostream>
#include "rendering/render_octree.h"
#include "core/primitives.h"
#include "core/bounds.h"

int main(){
    engine_t engine;

    if (!engine.initialise()){
        std::cout << "Engine failed to initialise. Aborting." << std::endl;
        return 1;
    }

    engine.run();

    engine.terminate();
    return 0;
}
