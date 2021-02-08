#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/applink.c>
#include <openssl/pem.h>

int Decrypt(std::string encrypt_text, int num)
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

    num = RSA_private_decrypt(num, cipher_text, plain_text_receiver, rsaPrivateKey, RSA_PKCS1_PADDING);

    printf("%s", plain_text_receiver);


    return num;
}




