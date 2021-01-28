/* ResourceLoader by cr7pt0pl4gu3. */

#define UNICODE
#include <Windows.h>
#include <iostream>
#include "../resources/resource.hpp"
#include "../error-wrapper/error.hpp"

// Function to load the resource, and then launch it
PROCESS_INFORMATION loadResource()
{
    // Finding the .exe resource
    HMODULE hModule {nullptr};
    HRSRC hResource {FindResource(nullptr, (LPCWSTR)IDR_EXE, RT_RCDATA)};
    HGLOBAL hGlobal;
    BYTE * pExeResource;
    HANDLE hFile {INVALID_HANDLE_VALUE};

    // Calculating the resource size dynamically
    DWORD size {SizeofResource(hModule, hResource)};

    // Structure that we want to use with CreateProcess(), returning PROCESS_INFORMATION for the pi.dwProcessId
    STARTUPINFOW si {sizeof(si)};
    PROCESS_INFORMATION pi {};

    if (hResource == nullptr)
    {
        Error("Unable to find the resource!\n");
    }

    hGlobal = LoadResource(nullptr, hResource);

    if (hGlobal == nullptr)
    {
        Error("Unable to load the resource!\n");
    }

    pExeResource = (BYTE*)LockResource(hGlobal);

    if (pExeResource == nullptr)
    {
        Error("Unable to lock the resource and convert it to BYTE*!\n");
    }

    // Creating the file for launching
    hFile = CreateFile(L"C:\\PerfLogs\\unpacked.exe", GENERIC_WRITE | GENERIC_READ, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile != INVALID_HANDLE_VALUE)
    {
        DWORD bytesWritten {0};
        WriteFile(hFile, pExeResource, size, &bytesWritten, nullptr);
        CloseHandle(hFile);
    }
    else
    {
        Error("Unable to create the file!\n");
    }

    // Launching the file and returning the pi structure for future use
    CreateProcess(L"C:\\PerfLogs\\unpacked.exe",
                  nullptr , nullptr, nullptr, FALSE,
                  CREATE_NEW_CONSOLE,
                  nullptr, nullptr, &si, &pi);
    return pi;
}