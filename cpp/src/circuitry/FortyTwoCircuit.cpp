#include "FortyTwoCircuit.hpp"

namespace zkpworkshop {

FortyTwoCircuit::FortyTwoCircuit() {
    in.allocate(pb);
    pb.add_r1cs_constraint(r1cs_constraint(in, 1, 42));
}

}