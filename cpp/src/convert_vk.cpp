#include <libsnark/common/default_types/r1cs_ppzksnark_pp.hpp>
#include <libsnark/gadgetlib1/pb_variable.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp>
#include "serialization.hpp"
#include "vk_output.hpp"

using namespace std;
using namespace zkpworkshop;

typedef libff::Fr<default_r1cs_ppzksnark_pp> FieldT;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "Need exactly 2 arguments (path to source vk, path to target vk)" << endl;
    return 1;
  }
  default_r1cs_ppzksnark_pp::init_public_params();

  auto vk = read_from_file<r1cs_ppzksnark_verification_key<default_r1cs_ppzksnark_pp>>(argv[1]);
  print_vk_to_file<default_r1cs_ppzksnark_pp>(vk, argv[2]);
  return 0;
}