#include <openssl/rsa.h>
#include <iostream>
#include <openssl/pem.h>
#include "encrypt_rsa.hpp"
#include "decrypt_rsa.hpp"
#include "include_rsa.hpp"



void Generate_Keys()
{
    RSA* key;
    BIGNUM* bne;
    BIO *bp_public, *bp_private;
    unsigned long e = RSA_F4;

    bne = BN_new();
    BN_set_word(bne, e);

    key = RSA_new();

    RSA_generate_key_ex(key, 2048, bne, nullptr);

    bp_public = BIO_new_file("public.txt", "w+");
    PEM_write_bio_RSAPublicKey(bp_public, key);

    bp_private = BIO_new_file("private.txt", "w+");
    PEM_write_bio_RSAPrivateKey(bp_private, key, nullptr, nullptr, 0, nullptr, nullptr);
}

int main() {

    int num;
    std::string encrypt_text;
    Generate_Keys();
    encrypt_text = Encrypt(num);
    Decrypt(encrypt_text, num);
    return 0;
}
