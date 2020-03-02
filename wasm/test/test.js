describe('The secp256k1 library', function() {

    it('can create a public key from a private key', function() {

		const privkey_address = 6000000			// memory address for the private key
		const pubkey_address = 5000000			// memory address for the public key
		window.a.HEAPU8[privkey_address+31] = 42	// example private key is 0x0000....0042
		window.a._wasm_secp256k1_ec_pubkey_create(pubkey_address, privkey_address) // create the public key from private key 
		const pubkey = a.HEAPU8.slice(pubkey_address, pubkey_address+33)	// read the resulting public key as Uint8Array

        const expected = new Uint8Array([2, 254, 141, 30, 177, 188, 179, 67, 43, 29, 181, 131, 63, 245, 242, 34, 109, 156, 181, 230, 92, 238, 67, 5, 88, 193, 142, 211, 163, 200, 108, 225, 175])
        expect(pubkey).toEqual(expected)
    })

})