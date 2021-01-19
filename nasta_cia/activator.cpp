#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include <string>

#pragma comment(lib, "Wsock32.lib")
#pragma comment(lib, "Ws2_32.lib")


int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
	struct sockaddr_in peer {};
	peer.sin_family = AF_INET;
	peer.sin_port = htons(5555);
	// т.к. клиент и сервер на одном компьютере, пишем адрес 127.0.0.1
	peer.sin_addr.s_addr;
	InetPton(AF_INET, "127.0.0.1", &peer.sin_addr.s_addr);
	//создаем сокет
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	//посылаем запрос на открытие соединения
	int requestStatus {connect(s, (struct sockaddr*) &peer, sizeof(peer))};
    std::string name {};
	char b[255], *end;
	printf("Enter your name to get a key\n");
    std::getline (std::cin, name);

    // Explain or redo
	const unsigned int len = name.length();
	const char* nameBuf = (const char*) &len;
	
	int status = send(s, nameBuf, 4, 0);
	if (status < 0)
	{
		printf("Send failed, status = %i\n", status);
		exit(1);
	}

	if (send(s, name.c_str(), name.length(), 0) < 0)
	{
		printf("Send failed\n");
		exit(1);
	}


	b[6] = '\0';	
	//принимаем данные
	if (recv(s, b, sizeof(b), 0) != 0) {
		printf("From server: %s\n", b);	
	}
	
	int key = strtol(b, &end, 10);

	Sleep(5000);
	system("cls");

	int userKey{};
	
	while (true)
	{
		printf("Enter your key\n");
		std::cin >> userKey;

		if (userKey == key)
		{
			printf("You are right, welcome.");
			break;
		}
		else
		{
			printf("Try again.");
		}
	}


	closesocket(s);
	WSACleanup();
	
}

