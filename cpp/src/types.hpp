#include <libsnark/common/default_types/r1cs_ppzksnark_pp.hpp>
#include <libsnark/gadgetlib1/protoboard.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp>


namespace zkpworkshop {
    typedef libsnark::default_r1cs_ppzksnark_pp r1cs_ppzksnark_pp;
    typedef libff::Fr<r1cs_ppzksnark_pp> FieldT;
    typedef libsnark::protoboard<FieldT> protoboard;
    typedef libsnark::pb_variable<FieldT> pb_variable;
    typedef libsnark::r1cs_constraint<FieldT> r1cs_constraint;
    typedef libsnark::r1cs_ppzksnark_proving_key<r1cs_ppzksnark_pp> r1cs_ppzksnark_proving_key;
    typedef libsnark::r1cs_ppzksnark_verification_key<r1cs_ppzksnark_pp> r1cs_ppzksnark_verification_key;
}
