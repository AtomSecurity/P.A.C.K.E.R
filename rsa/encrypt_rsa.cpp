#include <iostream>
#include <string>
#include <fstream>
#include <openssl/rsa.h>
#include <openssl/pem.h>


unsigned char* Encrypt(std::string text) {

    unsigned char plain_text_sender[17]{};
    static unsigned char cipher_text[256]{};

    // Copy data from string to unsigned char
    std::copy(text.begin(), text.end(), plain_text_sender);

    // Open file with public key
    FILE *fp;
    fopen_s(&fp, "public.txt", "rt");

    // Create variable for public key
    RSA *rsaPublicKey = PEM_read_RSAPublicKey(fp, nullptr, nullptr, nullptr);

    // Close file
    fclose(fp);


    // Encrypt data with public key
    RSA_public_encrypt(sizeof(plain_text_sender) - 1, plain_text_sender, cipher_text, rsaPublicKey, RSA_PKCS1_PADDING);

    // Encrypted data
    return cipher_text;
}


