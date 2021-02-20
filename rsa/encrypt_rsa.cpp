#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>


std::string Encrypt(int& num) {

    std::string str;
    std::getline(std::cin, str);

    unsigned char plain_text_sender[17] {};
    unsigned char cipher_text[256] {};

    std::copy(str.begin(), str.end(), plain_text_sender);

    FILE *fp;
    fopen_s(&fp, "public.txt", "rt");

    RSA *rsaPublicKey = PEM_read_RSAPublicKey(fp, nullptr, nullptr, nullptr);

    fclose(fp);

    num = RSA_public_encrypt(sizeof(plain_text_sender) - 1, plain_text_sender, cipher_text, rsaPublicKey,
                             RSA_PKCS1_PADDING);

    std::string encrypt_text;

    for (unsigned char i : cipher_text)
    {
        encrypt_text += i;
        //printf("%x", i);
        std::cout << std::hex << static_cast<int>(i);
    }

    std::cout << std::endl;
    return encrypt_text;
}


