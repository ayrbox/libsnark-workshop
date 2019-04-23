#include <iostream>
#include <libff/algebra/curves/public_params.hpp>
#include "circuitry/FortyTwoCircuit.hpp"

using namespace std;
using namespace zkpworkshop;

int main() {

    libsnark::default_r1cs_ppzksnark_pp::init_public_params();

    FortyTwoCircuit ftc;

    auto cs = ftc.pb.get_constraint_system();
    if (cs.is_satisfied(ftc.pb.primary_input(), ftc.pb.auxiliary_input())) {
        cout << "Constraint system is satisfied." << endl;
    } else {
        cout << "Constraint system is NOT satisfied." << endl;
    }

    ftc.pb.val(ftc.in) = 42;

    if (cs.is_satisfied(ftc.pb.primary_input(), ftc.pb.auxiliary_input())) {
        cout << "Constraint system is satisfied." << endl;
    } else {
        cout << "Constraint system is NOT satisfied." << endl;
    }

}
