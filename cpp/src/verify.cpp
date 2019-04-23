#include <string>
#include <libff/algebra/curves/public_params.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp>
#include "types.hpp"
#include "circuitry/FortyTwoCircuit.hpp"
#include "serialization.hpp"

using namespace std;
using namespace zkpworkshop;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Need at least 2 arguments (path to vk, path to proof)" << endl;
        return 1;
    }

    libsnark::default_r1cs_ppzksnark_pp::init_public_params();

    auto vk_path = argv[1];
    auto proof_path = argv[2];
    cout << vk_path << endl;
    cout << proof_path << endl;
    auto vk = read_from_file<r1cs_ppzksnark_verification_key>(argv[1]);
    auto proof = read_from_file<r1cs_ppzksnark_proof>(argv[2]);

    std::vector<FieldT> public_inputs;
    for (size_t i = 3; i < argc; i++) {
        string val = argv[i];
        public_inputs.push_back(FieldT(val.c_str()));
    }
    bool verified = libsnark::r1cs_ppzksnark_verifier_strong_IC<r1cs_ppzksnark_pp>(vk, public_inputs, proof);
    if (verified) {
        cout << "Successfully verified." << endl;
    } else {
        cerr << "Verification failed." << endl;
    }
    return 0;
}
