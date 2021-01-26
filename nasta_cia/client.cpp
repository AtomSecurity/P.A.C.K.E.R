//#define UNICODE
#include "pch.h"
#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iterator>

#pragma comment(lib, "Wsock32.lib")
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main()
{
	
	WORD wVersionRequested{ MAKEWORD(2, 2) };
	WSADATA wsaData;
	WSAStartup(wVersionRequested, &wsaData);
	struct sockaddr_in peer {};
	peer.sin_family = AF_INET;
	peer.sin_port = htons(5555);

	// т.к. клиент и сервер на одном компьютере, пишем адрес 127.0.0.1
	peer.sin_addr.s_addr;
	InetPton(AF_INET, L"127.0.0.1", &peer.sin_addr.s_addr);

	//создаем сокет
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	//посылаем запрос на открытие соединения
	int requestStatus{ connect(s, (struct sockaddr*) &peer, sizeof(peer)) };
	

	std::string email{0};
	char secretKey[26];

	int Case;
	std::cout<<"Choose your operation: 1 - get a key(if you don`t have); 2 - verify"<<std::endl;
	std::cin >> Case;

	// sending case 
	int status{ send(s, (char*)&Case, 4, 0) };
	if (status < 0)
	{
		std::cout << "Send failed, status = " << status << std::endl;
		exit(1);
	}
	
	//case 1, getting key
	if (Case == 1)
	{

		std::cout << "Enter your email to get a key -> ";
		cin.ignore();
		getline(cin, email);

		// for email length passing
		const unsigned int len{ email.length() };
		const char* emailBuf{ (const char*)&len };
	
		int status{ send(s, emailBuf, 4, 0) };
		if (status < 0)
		{
			std::cout << "Send failed, status = " << status << std::endl;
			exit(1);
		}

		if (send(s, email.c_str(), email.length(), 0) < 0)
		{
			std::cout << "Send failed" << std::endl;
			exit(1);
		}

		// принимаем данные
		if (recv(s, secretKey, sizeof(secretKey), 0) != 0) {
			secretKey[25] = '\0';
		}
		else
		{
			std::cout << "Could not receive server answer." << std::endl;
			exit(1);
		}

		std::cout<<"Your key: "<<secretKey<<std::endl;
	}

	// case 2, checking key
	else if (Case == 2)
	{
		std::string userKey{};

		std::cout << "Enter your e-mail  -> ";
		std::cin >> email;

		std::cout << "Enter your key -> ";
		std::cin >> userKey;
		std::cout << std::endl;

		// for email length passing
		const unsigned int len{ email.length() };
		const char* emailBuf{ (const char*)&len };


		int status{ send(s, emailBuf, 4, 0) };
		if (status < 0)
		{
			std::cout << "Send failed, status = " << status << std::endl;
			exit(1);
		}

		if (send(s, email.c_str(), email.length(), 0) < 0)
		{
			std::cout << "Send failed" << std::endl;
			exit(1);
		}

		// key passing
		if (send(s, userKey.c_str(), 25, 0) < 0)
		{
			std::cout << "Send failed" << std::endl;
			exit(1);
		}
		char result;

		// checking
		if (recv(s, &result, 4, 0) < 0)
		{
			std::cout << "Recv failed." << std::endl;
		}

		if (result == '1')
		{
			std::cout << "You are authorized." << std::endl;
		}
		else
		{
			std::cout << "Try again." << std::endl;
		}
		
	}

	closesocket(s);
	
	WSACleanup();

}
