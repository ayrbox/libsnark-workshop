// This file is MIT Licensed.
//
// Copyright 2017 Christian Reitwiessner
// Modified by Mario Gemoll
// Parts copied from the libsnark tutorial by Christian Lundkvist
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

pragma solidity ^0.5.3;

import 'Pairing.sol';

contract ____CONTRACT_NAME____ {

    using Pairing for *;

    struct VerifyingKey {
        Pairing.G2Point A;
        Pairing.G1Point B;
        Pairing.G2Point C;
        Pairing.G2Point gamma;
        Pairing.G1Point gammaBeta1;
        Pairing.G2Point gammaBeta2;
        Pairing.G2Point Z;
        Pairing.G1Point[] IC;
    }

    struct Proof {
        Pairing.G1Point A;
        Pairing.G1Point A_p;
        Pairing.G2Point B;
        Pairing.G1Point B_p;
        Pairing.G1Point C;
        Pairing.G1Point C_p;
        Pairing.G1Point K;
        Pairing.G1Point H;
    }

    function verifyingKey() internal pure returns (VerifyingKey memory vk) {
____VERIFYING_KEY_BODY____
    }

    function verify(uint[] memory input, Proof memory proof) internal returns (uint) {
        VerifyingKey memory vk = verifyingKey();
        require(input.length + 1 == vk.IC.length);
        // Compute the linear combination vk_x
        Pairing.G1Point memory vk_x = Pairing.G1Point(0, 0);
        for (uint i = 0; i < input.length; i++)
            vk_x = Pairing.pointAdd(vk_x, Pairing.scalarMul(vk.IC[i + 1], input[i]));
        vk_x = Pairing.pointAdd(vk_x, vk.IC[0]);
        if (!Pairing.pairingProd2(proof.A, vk.A, Pairing.negate(proof.A_p), Pairing.P2())) return 1;
        if (!Pairing.pairingProd2(vk.B, proof.B, Pairing.negate(proof.B_p), Pairing.P2())) return 2;
        if (!Pairing.pairingProd2(proof.C, vk.C, Pairing.negate(proof.C_p), Pairing.P2())) return 3;
        if (!Pairing.pairingProd3(
            proof.K, vk.gamma,
            Pairing.negate(Pairing.pointAdd(vk_x, Pairing.pointAdd(proof.A, proof.C))), vk.gammaBeta2,
            Pairing.negate(vk.gammaBeta1), proof.B
        )) return 4;
        if (!Pairing.pairingProd3(
                Pairing.pointAdd(vk_x, proof.A), proof.B,
                Pairing.negate(proof.H), vk.Z,
                Pairing.negate(proof.C), Pairing.P2()
        )) return 5;
        return 0;
    }

    event Verified(string);

    function verifyProof(
            uint[18] memory flattenedProof,
            uint[] memory input) public returns (bool r) {
        Proof memory proof;
        proof.A = Pairing.G1Point(flattenedProof[0], flattenedProof[1]);
        proof.A_p = Pairing.G1Point(flattenedProof[2], flattenedProof[3]);
        proof.B = Pairing.G2Point([flattenedProof[4], flattenedProof[5]], [flattenedProof[6],flattenedProof[7]]);
        proof.B_p = Pairing.G1Point(flattenedProof[8], flattenedProof[9]);
        proof.C = Pairing.G1Point(flattenedProof[10], flattenedProof[11]);
        proof.C_p = Pairing.G1Point(flattenedProof[12], flattenedProof[13]);
        proof.H = Pairing.G1Point(flattenedProof[14], flattenedProof[15]);
        proof.K = Pairing.G1Point(flattenedProof[16], flattenedProof[17]);
        uint[] memory inputValues = new uint[](input.length);
        for(uint i = 0; i < input.length; i++){
            inputValues[i] = input[i];
        }
        if (verify(inputValues, proof) == 0) {
            emit Verified("Transaction successfully verified.");
            return true;
        } else {
            return false;
        }
    }
}
