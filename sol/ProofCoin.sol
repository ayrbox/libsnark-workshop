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
        if (verifier.verifyProof(proof, publicInputs)) {
            emit CorrectProof();
            _mint(msg.sender, 1 ether);
        } else {
            emit IncorrectProof();
        }
    }

}