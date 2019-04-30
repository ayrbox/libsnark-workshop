#include "VitaliksExampleCircuitGadget.hpp"

namespace zkpworkshop {

VitaliksExampleCircuitGadget::VitaliksExampleCircuitGadget(
    protoboard &pb, const pb_variable &out, const pb_variable &x)
    : Gadget(pb, "VitaliksExampleCircuitGadget"), out(out), x(x) {
    sym_1.allocate(pb, "sym_1");
    y.allocate(pb, "y");
    sym_2.allocate(pb, "sym_2");
}

void VitaliksExampleCircuitGadget::generate_r1cs_constraints() {
    pb.add_r1cs_constraint(r1cs_constraint(x, x, sym_1), "x*x=sym_1");
    pb.add_r1cs_constraint(r1cs_constraint(sym_1, x, y), "sym_1*x=y");
    pb.add_r1cs_constraint(r1cs_constraint(y + x, 1, sym_2), "(y+x)*1=sym_2");
    pb.add_r1cs_constraint(r1cs_constraint(sym_2 + 5, 1, out), "(sym_2+5)*1=out");
}

void VitaliksExampleCircuitGadget::generate_r1cs_witness() {
    pb.val(sym_1) = pb.val(x) * pb.val(x);
    // std::cout << "x " << pb.val(x) << std::endl;
    // std::cout << "sym_1 " << pb.val(sym_1) << std::endl;
    pb.val(y) = pb.val(sym_1) * pb.val(x);
    // std::cout << "y " << pb.val(y) << std::endl;
    pb.val(sym_2) = pb.val(y) + pb.val(x);
    // std::cout << "sym_2 " << pb.val(sym_2) << std::endl;
    pb.val(out) = pb.val(sym_2) + 5;
    // std::cout << "out " << pb.val(out) << std::endl;
    // std::cout << "ha " << std::endl;
}

} // namespace zkpworkshop
