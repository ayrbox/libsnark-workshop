#include <iostream>
#include "circuitry/FortyTwoCircuit.hpp"

using namespace std;
using namespace zkpworkshop;

int main() {
    cout << "hello world" << endl;

    FortyTwoCircuit ftc;
    auto cs = ftc.pb.get_constraint_system();
}
