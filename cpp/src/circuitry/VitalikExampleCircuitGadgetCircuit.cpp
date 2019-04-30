#include "VitalikExampleCircuitGadgetCircuit.hpp"

namespace zkpworkshop {

VitaliksExampleCircuitGadgetCircuit::VitaliksExampleCircuitGadgetCircuit() {
    out.allocate(pb, "out");
    x.allocate(pb, "x");
    pb.set_input_sizes(1);
    gadget = new VitaliksExampleCircuitGadget(pb, out, x);
    gadget->generate_r1cs_constraints();
}

} // namespace zkpworkshop
