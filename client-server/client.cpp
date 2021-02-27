#define UNICODE
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <cstdlib>
#include <fstream>
#include <string>

#include <vector>

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

void encryptToFile (std::string aesEnc, std::string aesKey)
{

    aesEnc = Encrypt(aesKey);
    /*//std::cout << "Aes encrypted text(before writing to file):\n" << aesEnc << std::endl;

    struct stat results {};
    // Буффер (std::unique_ptr), динамически выделяется для char* на наш файл (чтобы считать его туда)
    auto buffer = std::make_unique<char[]>(results.st_size);
    std::ofstream nextFile;

    // Снова открываю файл с привилегиями in, out, binary и записываю туда данные из моей переменной
    nextFile.open("AesKey.txt", std::ios::in | std::ios::out | std::ios::binary);
    nextFile.write(buffer.get(), results.st_size);

    // Закрываю файл
    nextFile.close();*/

    /*std::ofstream oFile("AesKey.txt", std::ios::binary|std::ios::out);
    //oFile.write((char*)&StringLength, sizeof(unsigned short int));
    oFile.write(aesEnc.c_str(), aesEnc.size());
    oFile.close();*/


    std::fstream file("AesKey.txt");
    std::cout << "Aes encrypted text(before writing to file):\n";
    for (size_t i {}; i < aesEnc.length(); ++i)
    {
        std::cout << aesEnc[i];
    }
    std::cout << std::endl;
    if(file.is_open())
    {
        file.write(aesEnc.c_str(), 256);
        //file << aesEnc;
    }
    else
        std::cout<<"File was`t opened";

    file.close();
}


/*static std::string Read(std::istream &stream, uint32_t count)
{
    std::string result(count, ' ');
    stream.read(&result[0], count);

    return result;
}*/

void readFileAndSend (SOCKET s, int aesLen)
{
    std::string aesEnc;
    // Записываем длинну файла в results.st_size
    struct stat results {};
    if (stat("AesKey.txt", &results) != 0)
    {
        std::cout<<("Cannot get the file size!")<<std::endl;
    }
    // Буффер (std::unique_ptr), динамически выделяется для char* на наш файл (чтобы считать его туда)
    auto buffer = std::make_unique<char[]>(256);


    // Открываю fstream с полномочиями in, out, binary
    std::fstream myFile;
    myFile.open("AesKey.txt", std::ios::in | std::ios::out | std::ios::binary);
    // Считываю бинарку в буффер, не забываю указывать size файла, и закрываю сам файл [buffer.get == char* buffer]
    myFile.read(buffer.get(), 256);
    myFile.close();

    aesEnc = buffer.get();
    std::cout << "\nAes encrypted (after reading from file):\n";
    for (auto& i : aesEnc)
    {
        std::cout << i;
    }
    std::cout << std::endl;





    sending(s, (char*)aesEnc.c_str(), aesLen);

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
	char secretKey[26]{};

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
        sending(s, (char*)emailBuf, 4);

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

		int aesLen{256};
		std::string aesEnc;

		// ОТКРОЙ ФАЙЛ rsa и передай из него строку

		//std::fstream file("public.txt");
        //записать с файла в переменную rsaPub ключ
        //file.close();


		if (result == '1')
		{
			std::cout << "You are authorized." << std::endl;

            // временная строка
            std::string aesKey{"plm122345"};

            // func 1
            encryptToFile(aesEnc, aesKey);

            // func 2
            readFileAndSend(s,aesLen);

            std::cout<<"\nWell done!"<<std::endl;
		}
		else
		{
			std::cout << "Try again." << std::endl;
		}
	}

	closesocket(s);
	
	WSACleanup();

}
