#include "utils/resources.h"

namespace resources {
    std::string
    readFromTextFile(std::string path){
        std::string fullpath = "../Resources/" + path;
        return "hello";
    }
}
