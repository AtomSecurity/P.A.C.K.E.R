#define UNICODE
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include "../rsa/include_rsa.hpp"
#include "../rsa/encrypt_rsa.hpp"

#pragma comment(lib, "Wsock32.lib")
#pragma comment(lib, "Ws2_32.lib")

void receive(SOCKET s, char* toReceive, int len)
{
    int status {recv(s, toReceive, len, 0)};
    if (status < 0)
    {
        std::cout << "Recv failed" << std::endl;
        exit(1);
    }
}

void sending(SOCKET s, char* toSend, int len)
{
    int status {send(s, toSend, len, 0)};
    if (status < 0)
    {
        std::cout << "Send failed" << std::endl;
        exit(1);
    }
}

void encryptToFile(std::string aesKey)
{
    unsigned char* aesEnc {Encrypt(aesKey)};

    std::ofstream file;
    // Delete file contents
    file.open("AesKey.txt", std::ofstream::out | std::ofstream::trunc);
    file.close();

    // Write encrypted binary key to file
    file.open("AesKey.txt", std::ios::out | std::ios::binary);
    if(file.is_open())
    {
        file.write((const char*)aesEnc, 256);
        file.close();
    }
    else
    {
        std::cout << "File was`t opened";
    }
}

std::string readFileAndSend(SOCKET s)
{
    unsigned char aesEnc [256];

    std::ifstream myFile;
    myFile.open("AesKey.txt", std::ios::in | std::ios::binary);

    if (!myFile) {
        std::cout << "File was`t opened" << std::endl;
        exit(1);
    }

    // Read from file
    if (!myFile.read((char*)aesEnc, 256))
    {
        std::cout << "File was`t read." << std::endl;
        exit(1);
    }
    myFile.close();

    sending(s, (char*) aesEnc, 256);

    char aesDec[256]{};
    receive(s, aesDec, 256);

    return aesDec;
}

SOCKET begining()
{
    WORD wVersionRequested{ MAKEWORD(2, 2) };
    WSADATA wsaData;
    WSAStartup(wVersionRequested, &wsaData);
    struct sockaddr_in peer {};
    peer.sin_family = AF_INET;
    peer.sin_port = htons(5555);

    // As client and server are on the same computer, write the address 127.0.0.1
    peer.sin_addr.s_addr;
    InetPton(AF_INET, L"127.0.0.1", &peer.sin_addr.s_addr);

    // Create socket
    SOCKET s {socket(AF_INET, SOCK_STREAM, 0)};

    // Send a connection open request
    int requestStatus { connect(s, (struct sockaddr*) &peer, sizeof(peer)) };

    return s;
}

std::string clientInit()
{
    SOCKET s = begining();

    std::string email;
	char secretKey[26]{};

	int choice;
	std::cout << "Choose your operation: 1 - get a key(if you don`t have); 2 - verify" << std::endl;
	std::cin >> choice;

	// Sending case
    sending(s, (char *) &choice, 4);
	
	// Case 1, getting key
	if (choice == 1)
	{
		std::cout << "Enter your email to get a key -> ";
		std::cin >> email;

		// For email length passing
		const unsigned int len{ static_cast<unsigned int>(email.length()) };
		const char* emailBuf{ (const char*)&len };
        sending(s, (char*)emailBuf, 4);

        sending(s, (char*)email.c_str(), email.length());

        // Checking on the same email in file
        int exist{};
        receive(s, (char *)&exist, 4);

        if (exist == 1)
        {
            std::cout << "You have already had a key on this email. Try to verify it." << std::endl;
            exit(0);
        }
        else
        {
            // Receiving generated key from server
            receive(s, secretKey, sizeof(secretKey));

            std::cout << "Your key: " << secretKey << std::endl;
            std::getchar();
            exit(0);
        }
	}

	// Case 2, checking key
	else if (choice == 2)
	{
		std::string userKey;

		// Entering email and key for verifying
		std::cout << "Enter your e-mail  -> ";
		std::cin >> email;

		std::cout << "Enter your key -> ";
		std::cin >> userKey;
		std::cout << std::endl;

		// For email length passing
		const unsigned int len{ static_cast<unsigned int>(email.length()) };
		const char* emailBuf{ (const char*)&len };

		sending(s, (char*)emailBuf, 4);

		sending(s, (char*)email.c_str(), email.length());

		// Key passing
		sending(s, (char*)userKey.c_str(), 25);
		char result {};

		// Checking
		receive(s, &result, 4);

		if (result == '1')
		{
			std::cout << "You are authorized." << std::endl;

            std::string aesDec {readFileAndSend(s)};
            return aesDec;
		}
		else
		{
			std::cout << "Try again." << std::endl;
            return "Error";
		}
	}
	else
    {
	    std::cout << "You entered the wrong number. Try again." << std::endl;
    }

	closesocket(s);
	
	WSACleanup();

}
