#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>

//https://www.dynamsoft.com/codepool/how-to-use-openssl-generate-rsa-keys-cc.html
//http://blog.naver.com/PostView.nhn?blogId=ambidext&logNo=221726104308

int main()
{
	RSA* key;
    unsigned char cipher_text[256];
    unsigned char plain_text_sender[] = "Hello";
    unsigned char plain_text_receiver[256];
    unsigned int num;
    BIGNUM* bne;
    BIO	*bp_public = nullptr, *bp_private = nullptr;
    unsigned long e = RSA_F4;


    bne = BN_new();
    BN_set_word(bne, e);

    key = RSA_new();

    int ret = RSA_generate_key_ex(key, 2048, bne, nullptr);

    bp_public = BIO_new_file("public.txt", "w+");
    ret = PEM_write_bio_RSAPublicKey(bp_public, key);

    bp_private = BIO_new_file("private.txt", "w+");
    ret = PEM_write_bio_RSAPrivateKey(bp_private, key, EVP_des_ede3_cbc(), nullptr, 0, nullptr, nullptr);

    num = RSA_public_encrypt(sizeof(plain_text_sender) - 1, plain_text_sender, cipher_text, key, RSA_PKCS1_PADDING);
    for(unsigned char i : cipher_text)
    {
        printf("%x", i);
    }
    std::cout << std::endl;

    num = RSA_private_decrypt(num, cipher_text, plain_text_receiver, key, RSA_PKCS1_PADDING);

    printf("%s", plain_text_receiver);

	return 0;
}