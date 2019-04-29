pragma solidity ^0.5.3;

import "openzeppelin-solidity/contracts/token/ERC20/ERC20.sol";
import "Verifier.sol";

contract ProofCoin is ERC20 {
    Verifier verifier;

    event CorrectProof();
    event IncorrectProof();

    constructor(address verifierAddress) public {
        verifier = Verifier(verifierAddress);
    }
    
    function verifyProof(uint[] memory publicInputs, uint[18] memory proof) public {
        if (verifier.verifyProof(
            [proof[0], proof[1]], // a
            [proof[2], proof[3]], // a_p
            [
                [proof[4], proof[5]], // b (0)
                [proof[6], proof[7]]  // b (1)
            ],
            [proof[8], proof[9]], // b_p
            [proof[10], proof[11]], // c
            [proof[12], proof[13]], // c_p
            [proof[14], proof[15]], // h
            [proof[16], proof[17]], // k
            publicInputs
        )) {
            emit CorrectProof();
            _mint(msg.sender, 1 ether);
        } else {
            emit IncorrectProof();
        }
    }

}