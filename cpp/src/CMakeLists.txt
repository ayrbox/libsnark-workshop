include_directories(.)

add_library(zkpworkshop circuitry/FortyTwoCircuit.cpp)

target_link_libraries(
    zkpworkshop

    snark
)
target_include_directories(
    zkpworkshop

    PUBLIC
    ${DEPENDS_DIR}/libsnark
    ${DEPENDS_DIR}/libsnark/depends/libff
    ${DEPENDS_DIR}/libsnark/depends/libfqfft
)

add_executable(test test.cpp)
target_link_libraries(test zkpworkshop)

add_executable(set_up set_up.cpp)
target_link_libraries(set_up zkpworkshop)

add_executable(prove prove.cpp)
target_link_libraries(prove zkpworkshop)