#include "src/secp256k1.c"

/** 
 *  Compute the public key for a secret key.
 *
 *  Returns: 1: secret was valid, public key stores
 *           0: secret was invalid, try again
 *  Out:    pubkey:     pointer to the created public key (cannot be NULL)
 *  In:     seckey:     pointer to a 32-byte private key (cannot be NULL)
 */
int wasm_secp256k1_ec_pubkey_create(
    unsigned char *pubkey_serialized,
    const unsigned char *seckey
){
    secp256k1_pubkey pubkey;
    // unsigned char seckey[32] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,42 };
    secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);

    if(!secp256k1_ec_pubkey_create(ctx, &pubkey, seckey)){
        return 0;
    }

    size_t outputlen = 33;
    return secp256k1_ec_pubkey_serialize(ctx, pubkey_serialized, &outputlen, &pubkey, SECP256K1_EC_COMPRESSED);
}