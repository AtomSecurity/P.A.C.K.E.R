#define UNICODE
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <cstdlib>
#include <string>
#include "../rsa/include_rsa.hpp"
#include "../rsa/encrypt_rsa.hpp"
#include "../string-encryption/strdecrypt.hpp"

#pragma comment(lib, "Wsock32.lib")
#pragma comment(lib, "Ws2_32.lib")

void receive(SOCKET s, char* toReceive, int len)
{
    if (recv(s, toReceive, len, 0) < 0) {
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

SOCKET begining()
{
    WORD wVersionRequested{ MAKEWORD(2, 2) };
    WSADATA wsaData;
    WSAStartup(wVersionRequested, &wsaData);
    struct sockaddr_in peer {};
    peer.sin_family = AF_INET;
    peer.sin_port = htons(5555);

    // as client and server are on the same computer, write the address 127.0.0.1
    peer.sin_addr.s_addr;
    InetPton(AF_INET, L"127.0.0.1", &peer.sin_addr.s_addr);

    // create socket
    SOCKET s {socket(AF_INET, SOCK_STREAM, 0)};

    // send a connection open request
    int requestStatus { connect(s, (struct sockaddr*) &peer, sizeof(peer)) };

    return s;
}

int main()
{
    SOCKET s = begining();

    std::string email;
	char secretKey[26];

	int choice;
	std::cout << "Choose your operation: 1 - get a key(if you don`t have); 2 - verify" << std::endl;
	std::cin >> choice;

	// sending case
    sending(s, (char *) &choice, 4);
	
	// case 1, getting key
	if (choice == 1)
	{

		std::cout << "Enter your email to get a key -> ";
		std::cin >> email;

		// for email length passing
		const unsigned int len{ static_cast<unsigned int>(email.length()) };
		const char* emailBuf{ (const char*)&len };
        int tmp{4};
        sending(s, (char*)emailBuf, tmp);

        sending(s, (char*)email.c_str(), email.length());

		// receiving data
		receive(s, secretKey, sizeof(secretKey));

		std::cout<<"Your key: "<<secretKey<<std::endl;
	}

	// case 2, checking key
	else if (choice == 2)
	{
		std::string userKey;

		std::cout << "Enter your e-mail  -> ";
		std::cin >> email;

		std::cout << "Enter your key -> ";
		std::cin >> userKey;
		std::cout << std::endl;

		// for email length passing
		const unsigned int len{ static_cast<unsigned int>(email.length()) };
		const char* emailBuf{ (const char*)&len };

		sending(s,(char*)emailBuf,4);

		sending(s,(char*)email.c_str(), email.length());

		// key passing
		sending(s,(char*)userKey.c_str(),25);
		char result {};

		// checking
		receive(s,&result,4);

		std::string rsa, aes;
		// ОТКРОЙ ФАЙЛ rsa и передай из него строку

		if (result == '1')
		{
			std::cout << "You are authorized." << std::endl;
			sending(s, (char*)rsa.c_str(), 16);
			receive(s, (char*)aes.c_str(), 16);
            std::string aesKey{"plm122345"};
            std::string enc_string = Encrypt(aesKey);
            sending(s, (char*)aesKey.c_str(), aesKey.length());

		}
		else
		{
			std::cout << "Try again." << std::endl;
		}
		
	}

	closesocket(s);
	
	WSACleanup();

}
