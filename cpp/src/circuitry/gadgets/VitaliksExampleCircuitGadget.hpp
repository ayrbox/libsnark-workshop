#pragma once

#include "types.hpp"

namespace zkpworkshop {

class VitaliksExampleCircuitGadget : public Gadget {
  private:
    pb_variable sym_1;
    pb_variable y;
    pb_variable sym_2;
  public:
    const pb_variable out;
    const pb_variable x;
    VitaliksExampleCircuitGadget(protoboard &pb, const pb_variable &out,
                                 const pb_variable &x);
    void generate_r1cs_constraints();
    void generate_r1cs_witness();
};

} // namespace zkpworkshop
