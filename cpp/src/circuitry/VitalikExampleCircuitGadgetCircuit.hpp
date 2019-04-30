#pragma once

#include "types.hpp"
#include "Circuit.hpp"
#include "circuitry/gadgets/VitaliksExampleCircuitGadget.hpp"

namespace zkpworkshop {

class VitaliksExampleCircuitGadgetCircuit : public Circuit {
  public:
    pb_variable out;
    pb_variable x;
    VitaliksExampleCircuitGadget *gadget;
    VitaliksExampleCircuitGadgetCircuit();
};

} // namespace zkpworkshop
