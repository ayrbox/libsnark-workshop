#include "VitaliksExampleCircuit.hpp"

namespace zkpworkshop {
  VitaliksExampleCircuit::VitaliksExampleCircuit() {
      out.allocate(pb, "out");

      x.allocate(pb, "x");
      sym_1.allocate(pb, "sym_1");
      y.allocate(pb, "y");
      sym_2.allocate(pb, "sym_2");

      pb.set_input_sizes(1);

      pb.add_r1cs_constraint(r1cs_constraint(x, x, sym_1));
      pb.add_r1cs_constraint(r1cs_constraint(sym_1, x, y));
      pb.add_r1cs_constraint(r1cs_constraint(y + x, 1, sym_2));
      pb.add_r1cs_constraint(r1cs_constraint(sym_2 + 5, 1, out));
  }
}
