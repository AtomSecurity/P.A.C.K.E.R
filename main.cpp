#include <iostream>
#include <Windows.h>

// #include "client.hpp"
#include "loader/loader.hpp"
#include "injector/injector.hpp"

// Snippet for checking if the current process is elevated or not
BOOL IsProcessElevated()
{
    BOOL fIsElevated {FALSE};
    HANDLE hToken {nullptr};
    TOKEN_ELEVATION elevation {};
    DWORD dwSize {};

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
    {
        std::cout << "\nFailed to get Process Token: " << GetLastError();
        goto Cleanup;  // if Failed, we treat as False
    }


    if (!GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &dwSize))
    {
        std::cout << "\nFailed to get Token Information: " << GetLastError();
        goto Cleanup;  // if Failed, we treat as False
    }

    fIsElevated = elevation.TokenIsElevated;

    Cleanup:
    if (hToken)
    {
        CloseHandle(hToken);
        hToken = nullptr;
    }
    return fIsElevated;
}

int main()
{
    std::cout << "Welcome to P.A.C.K.E.R!\n";

    // Checking if run with admin rights
    if (!IsProcessElevated())
    {
        std::cout << "You need to run the program with administrator privileges! Quitting...";
        Sleep(5000);
        return 1;
    }

    // Loading the resource and launching .exe from it
    PROCESS_INFORMATION pi {loadResource()};

    Sleep(1000);
    // Injecting the security dll thread into the newly launched executable
    injectThread(pi.dwProcessId);
}
