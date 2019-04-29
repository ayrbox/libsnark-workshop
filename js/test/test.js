'use strict'

const assert = require('assert')
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
    const aliceBalanceBefore = await proofCoin.methods.balanceOf(alice.address).call()
    expect(aliceBalanceBefore).to.equal('0')
    const proof = await loadProof('/tmp/proof')
    const result = await sendTransaction(
      web3,
      proofCoin._address,
      proofCoin.methods.verifyProof([], proof).encodeABI(),
      alice
    )
    assert(_.some(_.map(result.logs, logEntry => {
      return _.first(logEntry.topics) === web3.utils.keccak256('CorrectProof()')
    })))
    const aliceBalanceAfter = await proofCoin.methods.balanceOf(alice.address).call()
    expect(aliceBalanceAfter).to.equal(web3.utils.toWei('1', 'ether'))
  })

})