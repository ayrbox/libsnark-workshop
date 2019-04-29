async function sendTransaction(web3, to, data, account = null, gas = 50000000, gasPrice = 0) {
  const txParams = {
    to,
    data,
    gas,
    gasPrice
  }
  if (account === null) {
    account = web3.eth.accounts.create()
  }
  const tx = await account.signTransaction(txParams)
  return web3.eth.sendSignedTransaction(tx.rawTransaction)
}

module.exports = sendTransaction