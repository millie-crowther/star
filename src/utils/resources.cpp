#include "utils/resources.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string
resources::readTextFile(std::string path){
    std::string fullpath = "../Resources/" + path;
    std::ifstream infile(fullpath);
    
    if (!infile.good()){
        return "";
    }

    std::stringstream buffer;
    buffer << infile.rdbuf();

    return buffer.str();
}
