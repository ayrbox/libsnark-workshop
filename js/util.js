const Web3 = require('web3')

function initWeb3() {
  const endpointFromEnv = process.env.ETHEREUM_JSONRPC_ENDPOINT
  return new Web3(endpointFromEnv || 'http://localhost:8545/')
}

function parseG1Point(data) {
	const X = data[0]
	const Y = data[1]
	return [X, Y]
}

function parseG2Point(data) {
	const X = [data[1], data[0]]
	const Y = [data[3], data[2]]
	return [X, Y]
}

module.exports = {
  initWeb3,
  parseG1Point,
  parseG2Point
}