#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>


void Decrypt(std::string encrypt_text)
{
    unsigned char cipher_text[256] {};
    unsigned char plain_text_receiver[256] {};

    for(int i = 0; i < encrypt_text.length(); i++)
    {
        cipher_text[i] = encrypt_text[i];
    }

    FILE* fp;
    fopen_s(&fp, "private.txt", "rt");

    RSA* rsaPrivateKey = PEM_read_RSAPrivateKey(fp, nullptr, nullptr, nullptr);

    RSA_private_decrypt(256, cipher_text, plain_text_receiver, rsaPrivateKey, RSA_PKCS1_PADDING);

    printf("%s", plain_text_receiver);
}




