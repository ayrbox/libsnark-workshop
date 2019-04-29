const sendTransaction = require('./send-transaction')

async function deploy(web3, contractArtefacts, args = [], account = null, gas = 5000000) {
  const contract = new web3.eth.Contract(contractArtefacts.abi)
  const data = contract.deploy({
    data: contractArtefacts.bytecode,
    arguments: args
  }).encodeABI()
  const receipt = await sendTransaction(web3, null, data, gas, account)
  return receipt.contractAddress
}

module.exports = deploy