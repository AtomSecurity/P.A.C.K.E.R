#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>


std::string Decrypt(const unsigned char *encrypt_text)
{

    unsigned char plain_text_receiver[256] {};

    // Open file with private key
    FILE* fp;
    fopen_s(&fp, "private.txt", "rt");

    // Create variable for private key
    RSA* rsaPrivateKey = PEM_read_RSAPrivateKey(fp, nullptr, nullptr, nullptr);

    fclose(fp);

    //Decrypt data with private key
    RSA_private_decrypt(256, encrypt_text, plain_text_receiver, rsaPrivateKey, RSA_PKCS1_PADDING);

    std::string decrypt_text;

    // From unsigned char to string
    for(unsigned char i : plain_text_receiver)
    {
        decrypt_text += i;
    }

    // Decrypted data
    return decrypt_text;
}