#include <ctime>
#include <winsock2.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#pragma comment(lib,"Wsock32.lib")


int main()
{
	std::cout << "Server is running ...\n";
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
	// создаем сокет
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in local{};
	local.sin_family = AF_INET;
	local.sin_port = htons(5555);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	// связываем сокет с адресом
	int bindAddress = bind(s, (struct sockaddr*)&local, sizeof(local));
	// помещаем сокет в состояние прослушивания
	listen(s, 5);
	while (true) {
		char res[100];
		
		//структура определяет удаленный адрес, с которым соединяется сокет
		sockaddr_in remote_addr{};
		int size = sizeof(remote_addr);
		//инитиялизируем соединение при запросе клиента
		SOCKET s2 = accept(s, (struct sockaddr*)&remote_addr, &size);
		//принимаем данные
		char nameBuf[4];
		int status = recv(s2, nameBuf, 4, 0);
		if (status < 0)
		{
			printf("recv failed, status = %d\n", status);
			exit(1);
		}

		// 2 lines of ??? code, either explain or redo!!!
		const auto* len_pointer = (const unsigned int*) &nameBuf;
		int intNameLen = *len_pointer;

		// char* name = (char*)malloc(intNameLen+1); Use this instead:
		char* name {new char[intNameLen+1]};

		if (recv(s2, name, intNameLen, 0) < 0)
		{
			printf("recv failed\n");
			exit(1);
		}
		name[intNameLen] = '\0';
		printf("From client: %s\n", name);

		// Cleaning char* name
		delete[] name;
		name = nullptr;

		// REDO RANDOM SEEDING
		srand(time(nullptr));
		int key = rand() % 899999 + 100000;
		printf("Key = %d\n", key);
			

		_itoa_s(key, res, 10);

		// Посылает данные на соединенный сокет
		if (send(s2, res, strlen(res), 0) < 0)
		{
			printf("send failed\n");
			exit(1);
		}
			
		//}
		closesocket(s2);
	}
    // WSACleanup(); Unreachable code

}