const asyncFs = require('./async-fs')
const execAsync = require('./exec-async')
const flattenProof = require('./flatten-proof')
const path = require('path')

async function loadProof(filePath) {
  const executable = path.join(__dirname, '..', 'cpp', 'build', 'src', 'convert_proof')
  const result = await execAsync(`${executable} ${filePath}`)
  return flattenProof(JSON.parse(result.stdout))
}

module.exports = loadProof