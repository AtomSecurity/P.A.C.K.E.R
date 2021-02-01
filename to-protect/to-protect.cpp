#define UNICODE
#include <iostream>
#include "../dll/security.hpp"

#pragma comment(lib, "security.lib")

int main()
{
    // Starting static .dll defense
    StaticDefense();

    // Maybe also check the hash of the thread to verify integrity
    std::cout << "Finished execution.";
    // exit(0); so the thread exits as well
}