'use strict'

const compileContracts = require('../compile-contracts')
const util = require('../util')
const _ = require('lodash')
const deploy = require('../deploy')
const expect = require('code').expect
const loadProof = require('../load-proof')
const sendTransaction = require('../send-transaction')

describe('Proof verification on chain', function () {

  let web3, proofCoin

  before(async function () {
    web3 = util.initWeb3()
    const artefacts = await compileContracts('/tmp/vk')
    const verifierAddr = await deploy(web3, artefacts.Verifier)
    const proofCoinAddr = await deploy(
      web3,
      artefacts.ProofCoin,
      [verifierAddr]
    )
    proofCoin = new web3.eth.Contract(artefacts.ProofCoin.abi, proofCoinAddr)
  })

  it('works', async function() {
    const alice = web3.eth.accounts.create()
    const aliceBalanceBefore = await proofCoin.methods.balanceOf(alice._address).call()
    expect(aliceBalanceBefore).to.equal('0')
    const proof = await loadProof('/tmp/proof')
    await sendTransaction(
      web3,
      proofCoin._address,
      proofCoin.methods.verifyProof([], proof).encodeABI(),
      50000000
    )
  })

})