#define UNICODE
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "../dll/security.hpp"

#pragma comment(lib, "security.lib")

int main()
{
    std::cout << "Checking the codeword...\n";
    std::string trueCodeWord {"cr7pt0pl4gu3"};

    if (trueCodeWord == GetCodeWord())
    {
        std::cout << "Everything is perfect!\n";
    }
    else
    {
        std::cout << "Something bad happened.\n";
    }

    std::cout << "Press any button to close the program...";
    std::cin.get();
}