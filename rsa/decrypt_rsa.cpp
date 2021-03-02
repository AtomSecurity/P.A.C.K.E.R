#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>


std::string Decrypt(const unsigned char *encrypt_text)
{
//    unsigned char cipher_text[256] {};
    unsigned char plain_text_receiver[256] {};

    FILE* fp;
    fopen_s(&fp, "private.txt", "rt");

    RSA* rsaPrivateKey = PEM_read_RSAPrivateKey(fp, nullptr, nullptr, nullptr);

    RSA_private_decrypt(256, encrypt_text, plain_text_receiver, rsaPrivateKey, RSA_PKCS1_PADDING);

    std::string decrypt_text;

    for(unsigned char i : plain_text_receiver)
    {
        decrypt_text += i;
    }

    return decrypt_text;
}