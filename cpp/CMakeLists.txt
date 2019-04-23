cmake_minimum_required(VERSION 3.13)

project(zkpworkshop)

set(
    CURVE
    "ALT_BN128"
    CACHE
    STRING
    "Default curve: one of ALT_BN128, BN128, EDWARDS, MNT4, MNT6"
)

set(
    DEPENDS_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/depends"
    CACHE
    STRING
    "Optionally specify the dependency installation directory relative to the source directory (default: inside dependency folder)"
)

option(
    BINARY_OUTPUT
    "In serialization, output raw binary data (instead of decimal), which is smaller and faster."
    OFF
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wfatal-errors -pthread")

add_definitions(-DCURVE_${CURVE})

add_subdirectory(depends)
add_subdirectory(src)
