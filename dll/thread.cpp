#define UNICODE
#include <Windows.h>
#include <iostream>
#include "thread.hpp"

[[noreturn]] void DynamicDefense()
{
    std::cout << "Performing dynamic checks.\n";
    // Launching the dynamic defense
    while (true)
    {
        // Do something
        Sleep(1000);
    }
}

bool isThreadSigned()
{
    // Check the thread somehow? Maybe connect to server, generate unique id and check it?
    return true;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, PVOID lpReserved)
{
    if (isThreadSigned())
    {
        DynamicDefense();
    }
    else
    {
        return FALSE; // Exit if thread is unvalidated
    }
}