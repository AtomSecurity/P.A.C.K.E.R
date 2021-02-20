#include <iostream>
#include <string>
#include <fstream>
#include <openssl/rsa.h>
#include <openssl/pem.h>


std::string Encrypt(std::string text) {

    unsigned char plain_text_sender[17]{};
    unsigned char cipher_text[256]{};

    std::copy(text.begin(), text.end(), plain_text_sender);

    FILE *fp;
    fopen_s(&fp, "public.txt", "rt");

    RSA *rsaPublicKey = PEM_read_RSAPublicKey(fp, nullptr, nullptr, nullptr);

    fclose(fp);

    RSA_public_encrypt(sizeof(plain_text_sender) - 1, plain_text_sender, cipher_text, rsaPublicKey, RSA_PKCS1_PADDING);

    std::string encrypt_text;

    for(unsigned char i : cipher_text)
    {
        encrypt_text += i;
        printf("%x", i);
    }

    std::cout << std::endl;
    std::ofstream out;
    out.open("encrypt.txt");
    if(out.is_open())
    {
        out << encrypt_text;
    }
    out.close();

    return encrypt_text;
}


