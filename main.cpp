#include <iostream>
#include <Windows.h>

#include "client-server/client.hpp"
#include "loader/loader.hpp"
#include "injector/injector.hpp"
#include "aes256/aes256encrypt.hpp"

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
    // Checking if run with admin rights
    if (!IsProcessElevated())
    {
        std::cout << "You need to run the program with administrator privileges! Quitting...";
        Sleep(5000);
        return 1;
    }

    std::cout << "Welcome to P.A.C.K.E.R!\n";
    std::cout << "Do you want to encrypt your data? [Not for users]\n";
    std::cout << "1 - NO, 2 - YES: ";
    short choice {};
    std::cin >> choice;
    if (choice == 2)
    {
        // Return aes string, encrypt with rsa, save to file
        std::string key {AES256Encrypt()};
        // Encrypt with RSA
        encryptToFile(key);
        return 0;
    }
    std::string aesDec {clientInit()};
    if (aesDec == "Error")
        exit(0);
    std::cout << "Aes key: " << aesDec << std::endl;

    // Loading the resource and launching .exe from it
    PROCESS_INFORMATION pi {loadResource(aesDec)};

    Sleep(1000);
    // Injecting the security dll thread into the newly launched executable
    injectThread(pi.dwProcessId);
}
