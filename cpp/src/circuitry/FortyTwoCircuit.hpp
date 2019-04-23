#pragma once

#include "types.hpp"
#include "Circuit.hpp"

namespace zkpworkshop {

class FortyTwoCircuit : public Circuit {
    public:
    pb_variable in;
    FortyTwoCircuit();
};

}
