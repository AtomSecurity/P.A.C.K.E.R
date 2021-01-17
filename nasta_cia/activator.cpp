#include <iostream>
#include <winsock2.h>
#include <cstdlib>
#include <cstdio>
#pragma comment(lib,"Wsock32.lib")


int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
	struct sockaddr_in peer{};
	peer.sin_family = AF_INET;
	peer.sin_port = htons(5555);
	// т.к. клиент и сервер на одном компьютере, пишем адрес 127.0.0.1
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");
	//создаем сокет
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	//посылаем запрос на открытие соединения
	connect(s, (struct sockaddr*) &peer, sizeof(peer));
	char* name = (char *)malloc(100);
	memset(name, 0, 100);
	char b[255];
	printf("Enter your name to get a key\n");
	std::cin >> name;
	const unsigned int len = strlen(name);
	const char* nameBuf = (const char*) &len;
	
	int status = send(s, nameBuf, 4, 0);
	if (status < 0)
	{
		printf("Send failed, status = %i\n", status);
		exit(1);
	}

	if (send(s, name, strlen(name), 0) < 0)
	{
		printf("Send failed\n");
		exit(1);
	}
	free(name);


	b[6] = '\0';	
	//принимаем данные
	if (recv(s, b, sizeof(b), 0) != 0) {
		printf("From server: %s\n", b);	
	}
	
	int key = atoi(b);

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
