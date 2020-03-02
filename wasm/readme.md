# Web Assembly Experiment

## DISCLAIMER: EXPERIMENTAL CODE
> THIS CODE IS INSECURE! DO NOT USE IN PRODUCTION!
> EXPECT BREAKING API CHANGES ANYTIME.

## Setup
[Emscripten](https://emscripten.org/docs/getting_started/downloads.html) is required. 

Note: You always have to source `./emsdk_env.sh` first in a new terminal session.

## Compile WASM
```bash
emcc wasm/secp256k1_wasm.c -I. -DUSE_NUM_NONE -DUSE_FIELD_10X26 -DUSE_SCALAR_8X32 -DUSE_FIELD_INV_BUILTIN -DUSE_SCALAR_INV_BUILTIN -DECMULT_WINDOW_SIZE=14 -DECMULT_GEN_PREC_BITS=4 -s EXPORTED_FUNCTIONS='["_wasm_secp256k1_ec_pubkey_create"]' -o wasm/secp256k1.html -Oz --closure 1 -fno-exceptions -s FILESYSTEM=0 --llvm-lto 1 -s ENVIRONMENT=web
```

## Execute WASM
```javascript
privkey_address = 6000000			// memory address for the private key
pubkey_address = 5000000			// memory address for the public key
a.HEAPU8[privkey_address+31] = 42	// example private key is 0x0000....0042
a._wasm_secp256k1_ec_pubkey_create(pubkey_address, privkey_address) // create the public key from private key 
pubkey = a.HEAPU8.slice(pubkey_address, pubkey_address+33)	// read the resulting public key as Uint8Array
```
Disclaimer: Actually we should use `malloc` here instead of the "large random addresses" `5000000` and `6000000`. This is just a hacky way to interact with minimum JS.

## WASM Environment 
To run the tests in your browser you have run a local web server such as `python -m SimpleHTTPServer`.
Run the tests by opening `http://localhost:8000/test/`.

## Results of the Experiment 
The following are results for the constant time signing code. The non-constant time verification code is not compiled here, and compiling them would significantly grow the output size. The LLVM compiler allows to make trade-offs between code size for performance optimizations.

- No optimizations: 177 kBytes 
- Min code size: 38 kBytes

