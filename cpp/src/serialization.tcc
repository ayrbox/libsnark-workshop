#pragma once

#include <fstream>
#include <sstream>
#include "serialization.hpp"

template<typename T>
void zkpworkshop::write_to_file(std::string path, T& obj) {
    std::stringstream ss;
    ss << obj;
    std::ofstream fh;
    fh.open(path, std::ios::binary);
    ss.rdbuf()->pubseekpos(0, std::ios_base::out);
    fh << ss.rdbuf();
    fh.flush();
    fh.close();
}

template<typename T>
T zkpworkshop::read_from_file(std::string path) {
    std::stringstream ss;
    std::ifstream fh(path, std::ios::binary);

    // TODO: more useful error if file not found
    assert(fh.is_open());

    ss << fh.rdbuf();

    fh.close();

    ss.rdbuf()->pubseekpos(0, std::ios_base::in);

    T obj;
    ss >> obj;
    ss.flush();

    return obj;
}