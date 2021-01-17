#include "pch.h"
#include <iostream>
//#include "stdafx.h"
#include <winsock2.h>
#include <stdlib.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>   // Needed for _wtoi
#pragma comment(lib,"Wsock32.lib")
#define _CRT_SECURE_NO_WARNINGS


int main(int argc, char ** argv)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
	struct sockaddr_in peer;
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
	scanf("%s\0", name);
	const unsigned int len = strlen(name);
	const char* nameBuf = (const char*) &len;
	
	int status = send(s, nameBuf, 4, 0);
	if (status < 0)
	{
		printf("send failed, status = %i\n", status);
		exit(1);
	}

	if (send(s, name, strlen(name), 0) < 0)
	{
		printf("send failed\n");
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

	int userKey = 0;
	
	while (true)
	{
		printf("Enter your key\n");
		scanf("%i", &userKey);

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

