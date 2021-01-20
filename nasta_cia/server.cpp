#define UNICODE
#include <random>
#include <string>
#include <winsock2.h>
#include <iostream>
#include <cstdlib>

#pragma comment(lib,"Wsock32.lib")

std::string generateRandomString(int max_length=25)
{
    std::string possible_characters {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<> dist(0, possible_characters.size() - 1);
    std::string strReturn {};

    for(size_t i {}; i < max_length; ++i)
    {
        int random_index {dist(engine)};
        strReturn += possible_characters[random_index];
    }

    return strReturn;
}

int main()
{
	std::cout << "Server is running ...\n" << std::endl;
	WORD wVersionRequested {MAKEWORD(2, 2)};
	WSADATA wsaData;
	WSAStartup(wVersionRequested, &wsaData);

	// создаем сокет
	SOCKET s {socket(AF_INET, SOCK_STREAM, 0)};
	struct sockaddr_in local {};
	local.sin_family = AF_INET;
	local.sin_port = htons(5555);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	// связываем сокет с адресом
	int bindAddress {bind(s, (struct sockaddr*)&local, sizeof(local))};
	// помещаем сокет в состояние прослушивания
	listen(s, 5);
	while (true) {
		//структура определяет удаленный адрес, с которым соединяется сокет
		sockaddr_in remote_addr {};
		int size {sizeof(remote_addr)};

		//инитиялизируем соединение при запросе клиента
		SOCKET s2 {accept(s, (struct sockaddr*)&remote_addr, &size)};

		//принимаем данные
		char emailBuf[4];
		int status {recv(s2, emailBuf, 4, 0)};
		if (status < 0)
		{
		    std::cout << "Recv failed, status = " << status << std::endl;
			continue;
		}

		// for email length passing
		const auto* len_pointer {(const unsigned int*) &emailBuf};
		unsigned int intemailLen {*len_pointer};

		char* email {new char[intemailLen+1]};

		if (recv(s2, email, static_cast<int>(intemailLen), 0) < 0)
		{

            std::cout << "Recv failed." << std::endl;
            continue;
		}
		email[intemailLen] = '\0';
		std::cout << "From client: " << email << std::endl;

		// Cleaning char* email
		delete[] email;
		email = nullptr;

		// Random key generation
		std::string key = generateRandomString();

		std::cout << "Key -> " << key << "\n" << std::endl;

		// Посылает данные на соединенный сокет
		if (send(s2, key.c_str(), key.length(), 0) < 0)
		{
		    std::cout << "Send failed." << std::endl;
            continue;
		}
			
		//}
		closesocket(s2);
	}
    // WSACleanup(); Unreachable code

}