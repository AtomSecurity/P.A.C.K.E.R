#include <iostream>
#include <string>
#include <fstream>
#include <openssl/rsa.h>
#include <openssl/pem.h>


unsigned char* Encrypt(std::string text) {

    unsigned char plain_text_sender[17]{};
    static unsigned char cipher_text[256]{};

    std::copy(text.begin(), text.end(), plain_text_sender);

    FILE *fp;
    fopen_s(&fp, "public.txt", "rt");

    RSA *rsaPublicKey = PEM_read_RSAPublicKey(fp, nullptr, nullptr, nullptr);

    fclose(fp);

    RSA_public_encrypt(sizeof(plain_text_sender) - 1, plain_text_sender, cipher_text, rsaPublicKey, RSA_PKCS1_PADDING);

    for (unsigned int i : cipher_text)
    {
        printf("%x", i);
    }
    std::cout << "\n\n";


    return cipher_text;
}


