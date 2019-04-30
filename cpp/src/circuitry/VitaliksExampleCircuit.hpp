#pragma once

#include "types.hpp"
#include "Circuit.hpp"
#include "VitaliksExampleCircuit.hpp"

namespace zkpworkshop {

  class VitaliksExampleCircuit : public Circuit {
     public:
      pb_variable out;
      pb_variable x;
      pb_variable sym_1;
      pb_variable y;
      pb_variable sym_2;
      VitaliksExampleCircuit();
  };
}
