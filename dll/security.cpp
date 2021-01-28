#define UNICODE
#include <Windows.h>
#include <iostream>
#include "security.hpp"

EXPORT void CALLBACK StaticDefense()
{
    std::cout << "Performing static checks.\n";
    // Launching the passive defense
}

bool isThreadSigned()
{
    // Check the thread somehow? Maybe connect to server, generate unique id and check it?
    StaticDefense();
    return true;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, PVOID lpReserved)
{
    // Perform actions based on the reason for calling.
    switch(fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // Initialize once for each new process.
            // Return FALSE to fail DLL load.
            std::cout << "Initializing security dll.\n";
            StaticDefense();
            break;

        case DLL_THREAD_ATTACH:
            // Do thread-specific initialization.
            std::cout << "Security thread attached.\n";

            // Checking if thread is not hollowed or replaced
            if (!isThreadSigned())
            {
                std::cout << "Unable to validate the thread.\n";
                exit(1);
            }
            break;

        case DLL_THREAD_DETACH:
            // Do thread-specific cleanup.
            std::cout << "Security thread disconnected.\n";
            exit(1);

        case DLL_PROCESS_DETACH:
            // Perform any necessary cleanup.
            exit(0);

        default:
            std::cout << "Something strange happened.\n";
            exit(1);
    }
    return TRUE;
}