#define UNICODE
#include <iostream>
#include "../dll/security.hpp"

#pragma comment(lib, "security.lib")

int main()
{
    // Starting static .dll defense
    StaticDefense();

    // Maybe also check the hash of the thread to verify integrity

    std::cout << "Press any button to close the program...";
    std::cin.get();
}