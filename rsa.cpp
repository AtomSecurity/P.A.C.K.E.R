/*#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>

//https://www.dynamsoft.com/codepool/how-to-use-openssl-generate-rsa-keys-cc.html
//http://blog.naver.com/PostView.nhn?blogId=ambidext&logNo=221726104308

int main()
{
    RSA* key;
    unsigned char cipher_text[256];
    unsigned char plain_text_sender[] = "RFlX4VISnxXahwh7E73qovsPJ+GmlSJq2e34r0VdqCg=";
    unsigned char plain_text_receiver[256];
    int num;
    BIGNUM* bne;
    BIO	*bp_public, *bp_private;
    unsigned long e = RSA_F4;


    bne = BN_new();
    BN_set_word(bne, e);

    key = RSA_new();

    RSA_generate_key_ex(key, 2048, bne, nullptr);

    bp_public = BIO_new_file("public.txt", "w+");
    PEM_write_bio_RSAPublicKey(bp_public, key);

    bp_private = BIO_new_file("private.txt", "w+");
    PEM_write_bio_RSAPrivateKey(bp_private, key, nullptr, nullptr, 0, nullptr, nullptr);

    num = RSA_public_encrypt(sizeof(plain_text_sender) - 1, plain_text_sender, cipher_text, key, RSA_PKCS1_PADDING);
    for(unsigned char i : cipher_text)
    {
        printf("%x", i);
    }
    std::cout << std::endl;

    num = RSA_private_decrypt(num, cipher_text, plain_text_receiver, key, RSA_PKCS1_PADDING);


    std::string final_str;
    for (auto& i : plain_text_receiver)
    {
        if (static_cast<int>(i) == 204)
        {
            break;
        }
        else
        {
            final_str += i;
        }
    }

    std::cout << final_str;
}*/
#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/applink.c>
#include <openssl/pem.h>


int main()
{
    //char publicKeyText[2048];
    std::string str;
    std::getline(std::cin, str);

    auto  plain_text_sender {new unsigned char[str.length()]};
    unsigned char cipher_text[256] {};

    //std::c(plain_text_sender, str.length(), str.c_str());
    std::copy(str.begin(), str.end(), plain_text_sender);

    std::cout << plain_text_sender << std::endl;

    //std::ifstream file("public.txt");
    //file.getline(publicKeyText, 2048, '?');

    //std::cout << publicKeyText << std::endl;
    //file.close();

    //BIO* bio = BIO_new_mem_buf(publicKeyText, -1);

    //BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    FILE* fp = fopen("public.txt", "rt");

    RSA* rsaPublicKey = PEM_read_RSAPublicKey(fp, nullptr, nullptr, nullptr);

    //BIO_free(bio);

    RSA_public_encrypt(sizeof(plain_text_sender) - 1, plain_text_sender, cipher_text, rsaPublicKey, RSA_PKCS1_PADDING);


    //std::cout << rsaPublicKey << std::endl;

    for(unsigned char i : cipher_text)
    {
        printf("%x", i);
    }
    delete[] plain_text_sender;
    plain_text_sender = nullptr;
    return 0;
}