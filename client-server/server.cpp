#define UNICODE
#include <random>
#include <string>
#include <WinSock2.h>
#include <iostream>
#include <fstream>
#include <string_view>
#include "../rsa/include_rsa.hpp"
#include "../rsa/decrypt_rsa.hpp"

#pragma comment(lib,"Wsock32.lib")

std::string generateRandomString(int max_length = 25)
{
    std::string possible_characters {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<> dist(0, possible_characters.size() - 1);
    std::string strReturn{};

    for (size_t i {}; i < max_length; ++i)
    {
        int random_index{ dist(engine) };
        strReturn += possible_characters[random_index];
    }

    return strReturn;
}

char checking(std::string_view findEmail, std::string_view findPass)
{
    std::fstream file("key_list.txt"); // open file

    while (!file.eof())
    {
        std::string email, pass;

        while (file >> email >> pass) // reading file line by line
        {
            int tmp {};
            if (email == findEmail)
            {
                ++tmp;
                std::cout << "Your email was found." << std::endl;
            }
            if (pass == findPass)
            {
                ++tmp;
                std::cout << "Your password was found." << std::endl;
            }
            if (tmp == 2)
            {
                file.close();
                std::cout << "You were verified." << std::endl;
                return '1';
            }
        }
        file.close();
        return '0';
    }
}

SOCKET startServer()
{
    std::cout << "Server is running ...\n" << std::endl;
    WORD wVersionRequested {MAKEWORD(2, 2)};
    WSADATA wsaData;
    WSAStartup(wVersionRequested, &wsaData);

    // create socket
    SOCKET s {socket(AF_INET, SOCK_STREAM, 0)};
    struct sockaddr_in local {};
    local.sin_family = AF_INET;
    local.sin_port = htons(5555);
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    // Connecting socket with address
    int bindAddress {bind(s, (struct sockaddr*)&local, sizeof(local))};
    // Put socket to a listening state
    listen(s, 5);
    return s;
}

void clean(const char* arr)
{
    delete[] arr;
    arr = nullptr;
}

void writeToFile(char* email, std::string_view key, unsigned int intEmailLen)
{
    std::fstream file;
    file.open("key_list");
    file.close();

    file.open("key_list.txt", std::ios::app);
    file.seekg(0, std::ios_base::end); // Put pointer to the end of file
    if (!file)
    {
        std::cout << "Error, file is not opened\n\n";
    }
    else
    {
        std::cout << "File is opened!\n\n";
    }
    file << std::string(email, intEmailLen);

    // Write key to file
    file << " " << key << std::endl;
    file.close();
}

int receive(SOCKET s, char* toReceive, int len)
{
    int status {recv(s, toReceive, len, 0)};
    if (status < 0)
    {
        std::cout << "Recv failed" << std::endl;
        return 1;
    }
    return 0;
}

int sending(SOCKET s, char* toSend, int len)
{
    int status {send(s, toSend, len, 0)};
    if (status < 0)
    {
        std::cout << "Send failed" << std::endl;
        return 1;
    }
    return 0;
}

int checkingEmailInFile(char* email)
{
    std::fstream file("key_list.txt"); // Open file

    while (!file.eof())
    {
        std::string readEmail, pass;

        while (file >> readEmail >> pass) // Reading file line by line
        {
            if (readEmail == email)
            {
                std::cout << "You have already had a key on this email." << std::endl;
                file.close();
                return 1;
            }
        }
        file.close();
        return 0;
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main()
{
    SOCKET s = startServer();
    while (true)
    {
        // The structure defines the remote address to which the socket connects
        sockaddr_in remote_addr {};
        int size {sizeof(remote_addr)};

        // Initialize the connection when the client requests
        SOCKET s2 {accept(s, (struct sockaddr*)&remote_addr, &size)};

        // Receiving case
        int choice {};
        int failure = receive(s2, (char*)&choice, 4);
        if (failure)
        {
            continue;
        }

        // Case 1
        if (choice == 1)
        {
            char emailBuf[4];
            failure = receive(s2, emailBuf, 4);
            if (failure)
            {
                continue;
            }

            // For email length passing
            const auto* len_pointer {(const unsigned int*)&emailBuf};
            unsigned int intemailLen {*len_pointer};

            char* email {new char[intemailLen + 1]};

            failure = receive(s2, email, static_cast<int>(intemailLen));
            if (failure)
            {
                continue;
            }

            email[intemailLen] = '\0';
            std::cout << "From client: " << email << std::endl;

            // Checking on the same email in file
            int exist = checkingEmailInFile(email);

            failure = sending(s2, (char*)&exist, 4);
            if (failure)
            {
                continue;
            }
            if (exist == 0)
            {
                // Random key generation
                std::string key = generateRandomString();
                std::cout << "Key -> " << key << "\n" << std::endl;

                failure = sending(s2, (char*)key.c_str(), key.length());
                if (failure)
                {
                    continue;
                }

                // Write email to file
                writeToFile(email, key, intemailLen);
            }
            // Cleaning char* email
            clean(email);
        }

            // Case 2
        else if (choice == 2)
        {
            char emailBuf[4];
            unsigned char pass[26] {};
            failure = receive(s2, emailBuf, 4);
            if (failure)
            {
                continue;
            }

            // For email length passing
            const auto* len_pointer {(const unsigned int*)&emailBuf};
            unsigned int intemailLen {*len_pointer};

            char* email {new char[intemailLen + 1]};

            failure = receive(s2, email, static_cast<int>(intemailLen));
            if (failure)
            {
                continue;
            }
            email[intemailLen] = '\0';
            std::cout << "From client: email: " << email << std::endl;

            failure = receive(s2, (char*)pass, 25);
            if (failure)
            {
                continue;
            }

            std::cout << "From client: password: " << pass << std::endl;

            // Checking if entered email and password are valid
            char result {checking(email, (char*)pass)};

            // Cleaning char* email
            clean(email);

            failure = sending(s2, &result, 4);
            if (failure)
            {
                continue;
            }

            if (result == '1')
            {
                std::cout << "You are authorized." << std::endl;

                std::string aesDec {};
                unsigned char aesEnc[256] {};

                failure = receive(s2, (char *)aesEnc, 256);
                if (failure)
                {
                    continue;
                }

                for (size_t i {}; i < 256; ++i)
                {
                    printf("%x", aesEnc[i]);
                }
                std::cout <<"\n\n";

                aesDec = Decrypt(aesEnc);
                std::cout << aesDec;

                failure = sending(s2, (char*)aesDec.c_str(), 256);
                if (failure)
                {
                    continue;
                }
            }
        }
        closesocket(s2);
    }
}
#pragma clang diagnostic pop

