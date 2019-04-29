#include <string>
#include <libff/algebra/curves/public_params.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp>
#include "types.hpp"
#include "circuitry/FortyTwoCircuit.hpp"
#include "serialization.hpp"

using namespace std;
using namespace zkpworkshop;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Need exactly 3 arguments (circuit type, path to pk, "
                  << "path to vk)" << std::endl;
        return 1;
    }

    libsnark::default_r1cs_ppzksnark_pp::init_public_params();

    string circuit_type = argv[1];

    Circuit circuit;

    if (circuit_type.compare("forty_two") == 0) {
        circuit = FortyTwoCircuit();
    } else {
        std::cerr << "Invalid circuit type" << endl;
        return 1;
    }

    auto cs = circuit.pb.get_constraint_system();
    auto keypair = libsnark::r1cs_ppzksnark_generator<r1cs_ppzksnark_pp>(cs);

    write_to_file<r1cs_ppzksnark_proving_key>(argv[2], keypair.pk);
    write_to_file<r1cs_ppzksnark_verification_key>(argv[3], keypair.vk);

    return 0;
}

