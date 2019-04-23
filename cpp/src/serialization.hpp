#pragma once

#include <string>

namespace zkpworkshop {

template<typename T>
void write_to_file(std::string path, T& obj);

template<typename T>
T read_from_file(std::string path);

}

#include "serialization.tcc"