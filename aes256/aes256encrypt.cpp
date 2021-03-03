#include "aes256.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <Windows.h>

#define BUFFER_SIZE 1024*1024

// Generating the key
std::string generateRandomString(int max_length = 16)
{
    std::string possible_characters{ "abcdefghijklmnopqrstuvwxyz" };
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<> dist(0, possible_characters.size() - 1);
    std::string strReturn{};

    for (size_t i{}; i < max_length; ++i)
    {
        int random_index{ dist(engine) };
        strReturn += possible_characters[random_index];
    }

    return strReturn;
}

void encrypt(char *ginput, char *gkey) {
    ByteArray key, enc;
    size_t file_len;
    FILE *input, *output;
    size_t key_len = 0;
    char *goutput = (char*)"tmp";
    while(gkey[key_len])
        key.push_back(gkey[key_len++]);
    fopen_s(&input, ginput, "rb");
    fopen_s(&output, goutput, "wb");
    Aes256 aes(key);
    _fseeki64(input, 0, SEEK_END);
    file_len = ftell(input);
    _fseeki64(input, 0, SEEK_SET);
    enc.clear();
    aes.encrypt_start(file_len, enc);
    fwrite(enc.data(), enc.size(), 1, output);
    while (!feof(input)) {
        auto *buffer = new unsigned char[BUFFER_SIZE];
        size_t buffer_len;
        buffer_len = fread(buffer, 1, BUFFER_SIZE, input);
        if (buffer_len > 0) {
            enc.clear();
            aes.encrypt_continue(buffer, buffer_len, enc);
            fwrite(enc.data(), enc.size(), 1, output);
        }
    }
    enc.clear();
    aes.encrypt_end(enc);
    fwrite(enc.data(), enc.size(), 1, output);
    fclose(input);
    fclose(output);
    CopyFile(goutput, ginput, 0);
}

std::string AES256Encrypt()
{
    std::cout << "*AES Encrypt v0.01*\n";

    std::vector<std::string> files;
    files.emplace_back("to-protect.exe");
    files.emplace_back("security.dll");
    files.emplace_back("thread.dll");

    std::string key {generateRandomString()};
    // std::string key {"abcdefghijklmnop"};

    for (auto& file : files)
    {
        char* cFile = file.data();
        char* cKey = key.data();
        encrypt(cFile, cKey);
    }
    return key;
}