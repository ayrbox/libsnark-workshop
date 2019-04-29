#pragma once

#include <json/json.h>
#include <libsnark/common/default_types/r1cs_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp>
#include "types.hpp"

namespace zkpworkshop
{

Json::Value to_json(r1cs_ppzksnark_proof proof);

}