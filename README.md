## Init Git submodules
```
git submodule update --init --recursive
```

## Build
In the `cpp` directory
```
mkdir build
cd build

CPPFLAGS="-I/usr/local/opt/openssl/include" \
LDFLAGS="-L/usr/local/opt/openssl/lib -L/usr/local/lib" \
PKG_CONFIG_PATH=/usr/local/opt/openssl/lib/pkgconfig \
cmake -DWITH_PROCPS=OFF -DWITH_SUPERCOP=OFF -DMULTICORE=OFF ..

make
```

## Smoke test for C++ stuff
```
cpp/build/src/set_up forty_two /tmp/pk /tmp/vk

cpp/build/src/prove forty_two /tmp/pk /tmp/proof 42

cpp/build/src/verify /tmp/vk /tmp/proof
```

## Install JS dependencies
In the `js` directory
```
npm i
```

## Run an Ethereum node (with 0 gas price)
```
docker run -p 8545:8545 appliedblockchain/parity-solo-instant
```

## Test proof verification on Ethereum
In the `js` directory
```
node_modules/.bin/mocha
```