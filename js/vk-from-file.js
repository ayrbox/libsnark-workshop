const assert = require('assert')
const readAndSplit = require('./read-and-split')
const u = require('./util')
const crypto = require('crypto')
const execAsync = require('./exec-async')
const path = require('path')

async function convertVk(src, dst) {
  const executable = path.join(__dirname, '..', 'cpp', 'build', 'src', 'convert_vk')
  await execAsync(`${executable} ${src} ${dst}`)
}

// Reads a verification key from a file.
async function vkFromFile(pathToVk, tmpDir = '/tmp') {
	const convertedVkPath = path.join(tmpDir, crypto.randomBytes(32).toString('hex'))
	await convertVk(pathToVk, convertedVkPath)
  let vk = await readAndSplit(convertedVkPath)
  assert(vk.length >= 24, 'vk too short')
	const A = u.parseG2Point(vk)
	vk = vk.slice(4)
	const B = u.parseG1Point(vk)
	vk = vk.slice(2)
	const C = u.parseG2Point(vk)
	vk = vk.slice(4)
	const gamma = u.parseG2Point(vk)
	vk = vk.slice(4)
	const gammaBeta1 = u.parseG1Point(vk)
	vk = vk.slice(2)
	const gammaBeta2 = u.parseG2Point(vk)
	vk = vk.slice(4)
	const Z = u.parseG2Point(vk)
	vk = vk.slice(4)
  const IC = []
	while(vk != [] && vk[0] != "") {
		IC.push(u.parseG1Point(vk))
		vk = vk.slice(2)
	}
  return [ A, B, C, gamma, gammaBeta1, gammaBeta2, Z, IC ]
}

module.exports = vkFromFile
