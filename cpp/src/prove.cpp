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
    if (argc < 4)
    {
        cerr << "Need at least 3 arguments (circuit type, path to pk, ";
        cerr << "path to proof)" << endl;
        return 1;
    }

    libsnark::default_r1cs_ppzksnark_pp::init_public_params();

    string circuit_type = argv[1];

    Circuit circuit;

    if (circuit_type.compare("42") == 0)
    {
        if (argc != 5)
        {
            cerr << "Need exactly 4 arguments (circuit type, path to pk, path ";
            cerr << "to proof, number)" << endl;
            return 1;
        }
        auto ft_circuit = FortyTwoCircuit();
        string number_val = argv[4];
        ft_circuit.pb.val(ft_circuit.in) = FieldT(number_val.c_str());
        circuit = ft_circuit;
    }
    else
    {
        std::cerr << "Invalid circuit type" << endl;
        return 1;
    }

    auto cs = circuit.pb.get_constraint_system();
    auto primary_input = circuit.pb.primary_input();
    auto auxiliary_input = circuit.pb.auxiliary_input();

    if (cs.is_satisfied(primary_input, auxiliary_input)) {
        cout << "Constraint system is satisfied." << endl;
    } else {
        cout << "Constraint system is NOT satisfied." << endl;
    }

    auto pk = read_from_file<r1cs_ppzksnark_proving_key>(argv[2]);

    auto proof = libsnark::r1cs_ppzksnark_prover<r1cs_ppzksnark_pp>(
        pk, primary_input, auxiliary_input);

    write_to_file<r1cs_ppzksnark_proof>(argv[3], proof);

    return 0;
}
