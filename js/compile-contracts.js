'use strict'

const _ = require('lodash')
const crypto = require('crypto')
const execAsync = require('./exec-async')
const path = require('path')
const asyncFs = require('./async-fs')
const vkFromFile = require('./vk-from-file')
const vkToSol = require('./vk-to-sol')

// Path to this project's contracts directory
const contractsSrcDir = path.join(
  path.parse(module.filename).dir,
  '..',
  'sol'
)

// Path to openzeppelin contracts
const ozDir = path.join(
  __dirname,
  'node_modules',
  'openzeppelin-solidity'
)

// Extracts abi and bytecode from solc output
function extractContractArtefacts(result, contractName) {
  const contractInfo = result.contracts[`${contractName}.sol:${contractName}`]
  return {
    abi: JSON.parse(contractInfo.abi),
    bytecode: '0x' + contractInfo.bin
  }
}

// Generates a verifier contract from a verifying key
async function generateVerifierContract(pathToVk, filePath, contractName) {
  // Read vk and Solidity contract source code template
  const templateFilePath = path.join(contractsSrcDir, 'GenericVerifier.sol')
  const [vk, contractTemplate] = await Promise.all([
    vkFromFile(pathToVk),
    asyncFs.readTextFile(templateFilePath)
  ])

  // Put contract name and vk into contract source, write to temporary file
  const vkSolSnippet = vkToSol(...vk)
  let contractSource = contractTemplate.replace('____CONTRACT_NAME____', contractName)
  contractSource = contractSource.replace('____VERIFYING_KEY_BODY____', vkSolSnippet)

  await asyncFs.writeTextFile(filePath, contractSource, 'utf8')

}

async function compileContracts(pathToVk, tmpDir = '/tmp') {
  const contractsDir = path.join(tmpDir, crypto.randomBytes(32).toString('hex'))
  await asyncFs.mkdir(contractsDir)

  const verifiers = [
    'Verifier'
  ]

  const normalContracts = [
    'ProofCoin',
    'Pairing'
  ]

  const contractNames = verifiers.concat(normalContracts)

  await generateVerifierContract(
    path.join(tmpDir, 'vk'),
    path.join(contractsDir, 'Verifier.sol'),
    'Verifier'
  )
  await Promise.all(normalContracts.map(name => {
    const filename = name + '.sol'
    return asyncFs.copyFile(
      path.join(contractsSrcDir, filename),
      path.join(contractsDir, filename)
    )
  }))

  const outputPath = path.join(contractsDir, 'output.json')
  const command = [
    `solc --combined-json abi,bin openzeppelin-solidity=${ozDir}`,
    `*.sol > output.json`
  ].join(' ')
  const options = {
    cwd: contractsDir,
    maxBuffer: 1024 * 1024
  }
  const {stdout, stderr} = await execAsync(command, options)
  if (stderr) {
    console.log(stderr)
  }
  const json = await asyncFs.readTextFile(outputPath)
  await Promise.all(contractNames.map(name => {
    return asyncFs.unlink(path.join(contractsDir, `${name}.sol`))
  }))
  //await asyncFs.unlink(contractsDir)
  const compilationResult = JSON.parse(json)

  return _.zipObject(
    contractNames,
    contractNames.map(contractName => {
      return extractContractArtefacts(compilationResult, contractName)
    })
  )

}

module.exports = compileContracts
