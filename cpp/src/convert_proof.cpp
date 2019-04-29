#include <libsnark/common/default_types/r1cs_ppzksnark_pp.hpp>
#include <libsnark/gadgetlib1/pb_variable.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp>
#include "types.hpp"
#include "serialization.hpp"
#include "json_conversion.hpp"

using namespace std;
using namespace zkpworkshop;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Need exactly 1 argument (path to proof)" << endl;
        return 1;
    }

    libsnark::default_r1cs_ppzksnark_pp::init_public_params();

    auto proof_path = argv[1];
    auto proof = read_from_file<r1cs_ppzksnark_proof>(argv[1]);
    cout << to_json(proof) << endl;
    return 0;
}