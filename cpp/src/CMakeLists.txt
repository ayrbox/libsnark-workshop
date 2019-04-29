include_directories(.)

add_library(zkpworkshop circuitry/FortyTwoCircuit.cpp json_conversion.cpp)

target_link_libraries(
    zkpworkshop

    jsoncpp
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

add_executable(verify verify.cpp)
target_link_libraries(verify zkpworkshop)

add_executable(convert_vk convert_vk.cpp)
target_link_libraries(convert_vk zkpworkshop)

add_executable(convert_proof convert_proof.cpp)
target_link_libraries(convert_proof zkpworkshop)