#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <fstream>
#include <sstream>

namespace resources {
    std::string
    readTextFile(std::string path){
	std::string filename = "../Resources/" + path;
        std::ifstream file(filename.c_str());

	std::stringstream buffer;
        buffer << file.rdbuf();
	return buffer.str();
    }
}

#endif
