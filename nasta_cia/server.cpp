//#define UNICODE
#include "pch.h"
#include <random>
#include <string>
#include <winsock2.h>
#include <iostream>
#include <cstdlib>
#include <fstream>

#pragma comment(lib,"Wsock32.lib")

std::string generateRandomString(int max_length = 25)
{
	std::string possible_characters{ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
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

char checking(std::string findName, std::string findPass)
{
	std::fstream file("d:\\AtomSecurity\\key_list.txt"); // открыли файл с текстом
	std::string name, pass;
	char c;

	while (!file.eof()) {  // прочитали его и заполнили им строку
		file.get(c);
		/*if (c == '|')
		{
			// проверить, совпадает ли строка с тем, что нужно найти
			// если совпадает, то продолжать запись в переменную pass
			if (name == findName)
			{
				name.push_back('\0');
				continue;
			}

		}
		else if (c == '\n')
		{
			pass.push_back('\0');
		}

		//если \n, то
		name.push_back(c);*/
		int tmp{ 0 };
		std::string name, pass;
		while (file >> name >> pass) // reading file line by line
		{
			tmp = 0;
			if (name == findName)
			{
				tmp++;
				std::cout << "Your name was found." << std::endl;
			}
			if (pass == findPass)
			{
				tmp++;
				std::cout << "Your password was found." << std::endl;
			}
			if (tmp == 2)
			{
				std::cout << "You were verified." << std::endl;
				return '1';
				break;
			}

		}
		if (tmp != 2)
		{
			return '0';
		}

	}

	file.close(); // обязательно закрыли

	/*std::cout << "enter a world for find: ";
	std::cin >> find;*/

	/*int pos = s.find(find); // поиск

	if (pos == -1)
	{
		std::cout << "not finded" << std::endl;
		return (false);
	}
	else
	{
		std::cout << "finded in " << pos << " simvol position" << std::endl;
		return (true);
	}*/


}

int main()
{
	std::cout << "Server is running ...\n" << std::endl;
	WORD wVersionRequested{ MAKEWORD(2, 2) };
	WSADATA wsaData;
	WSAStartup(wVersionRequested, &wsaData);

	// создаем сокет
	SOCKET s{ socket(AF_INET, SOCK_STREAM, 0) };
	struct sockaddr_in local {};
	local.sin_family = AF_INET;
	local.sin_port = htons(5555);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	// связываем сокет с адресом
	int bindAddress{ bind(s, (struct sockaddr*)&local, sizeof(local)) };
	// помещаем сокет в состояние прослушивания
	listen(s, 5);
	while (true) {
		// структура определяет удаленный адрес, с которым соединяется сокет
		sockaddr_in remote_addr{};
		int size{ sizeof(remote_addr) };

		// инитиялизируем соединение при запросе клиента
		SOCKET s2{ accept(s, (struct sockaddr*)&remote_addr, &size) };

		// receiving case 
		int Case;
		int status{ recv(s2, (char*)&Case, 4, 0) };
		if (status < 0)
		{
			std::cout << "Recv failed, status = " << status << std::endl;
			continue;
		}
		
		//case 1
		if (Case == 1)
		{
			// принимаем данные
			char emailBuf[4];
			int status{ recv(s2, emailBuf, 4, 0) };
			if (status < 0)
			{
				std::cout << "Recv failed, status = " << status << std::endl;
				continue;
			}

			// for email length passing
			const auto* len_pointer{ (const unsigned int*)&emailBuf };
			unsigned int intemailLen{ *len_pointer };

			char* email{ new char[intemailLen + 1] };


			if (recv(s2, email, static_cast<int>(intemailLen), 0) < 0)
			{
				std::cout << "Recv failed." << std::endl;
				continue;
			}
			email[intemailLen] = '\0';
			std::cout << "From client: " << email << std::endl;

			// write email to file
			std::fstream file("D:\\AtomSecurity\\key_list.txt", std::ios::app);
			file.seekg(0, std::ios_base::end); //Стать в конец файла
			if (!file)
			{
				std::cout << "Error, file is not opened\n\n";
			}
			else
			{
				std::cout << "File is opened!\n\n";
			}
			std::string email2(email, intemailLen);
			file << email2;


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

			// write key to file
			file << " " << key << std::endl;
			file.close();
		}
		
		//case 2
		else if (Case == 2)
		{
			char emailBuf[4], pass[26];
			int status{ recv(s2, emailBuf, 4, 0) };
			if (status < 0)
			{
				std::cout << "Recv failed, status = " << status << std::endl;
				continue;
			}

			// for email length passing
			const auto* len_pointer{ (const unsigned int*)&emailBuf };
			unsigned int intemailLen{ *len_pointer };

			char* email{ new char[intemailLen + 1] };


			if (recv(s2, email, static_cast<int>(intemailLen), 0) < 0)
			{
				std::cout << "Recv failed." << std::endl;
				continue;
			}
			email[intemailLen] = '\0';
			std::cout << "From client: email: " << email << std::endl;
			
			if (recv(s2, pass, 25, 0) < 0)
			{
				std::cout << "Recv failed." << std::endl;
				continue;
			}
			pass[25] = '\0';
			std::cout << "From client: password: " << pass << std::endl;

			char result{ checking(email, pass) };

			if (send(s2, &result, 4, 0) < 0)
			{
				std::cout << "Send failed." << std::endl;
			}
		}

		closesocket(s2);
	}
	// WSACleanup(); Unreachable code

}

