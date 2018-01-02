#include "core/engine.h"
#include <iostream>

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
