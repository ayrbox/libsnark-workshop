#include <libsnark/common/default_types/r1cs_ppzksnark_pp.hpp>
#include <libsnark/gadgetlib1/protoboard.hpp>

namespace zkpworkshop {
    typedef libff::Fr<libsnark::default_r1cs_ppzksnark_pp> FieldT;
    typedef libsnark::protoboard<FieldT> protoboard;
}
