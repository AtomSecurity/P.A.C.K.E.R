#define UNICODE
#include <Windows.h>
#include "resources/resource.hpp"
#include <iostream>

int createAndLaunchResource()
{
    HRSRC hrsrc {FindResource(nullptr, (LPCWSTR)IDR_EXE, RT_RCDATA)};
    HGLOBAL hGlbl;
    BYTE * pExeResource;
    HANDLE hFile {INVALID_HANDLE_VALUE};
    DWORD size {24576};

    if (hrsrc == nullptr)
    {
        std::cout << "hrsrc == nullptr" << std::endl;
        return 1;
    }

    hGlbl = LoadResource(nullptr, hrsrc);

    if (hGlbl == nullptr)
    {
        std::cout << "hGlbl == nullptr" << std::endl;
        return 1;
    }

    pExeResource = (BYTE*)LockResource(hGlbl);

    if (pExeResource == nullptr)
    {
        std::cout << "pExeResource == nullptr" << std::endl;
        return 1;
    }

    hFile = CreateFile(L"C:\\PerfLogs\\unpacked.exe", GENERIC_WRITE | GENERIC_READ, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile != INVALID_HANDLE_VALUE)
    {
        std::cout << "hFile != INVALID_HANDLE_VALUE" << std::endl;
        DWORD bytesWritten {0};
        WriteFile(hFile, pExeResource, size, &bytesWritten, nullptr);
        CloseHandle(hFile);
    }
    ShellExecute(nullptr, L"open", L"C:\\PerfLogs\\unpacked.exe", nullptr, nullptr, SW_SHOWNORMAL);
    return 0;
}

int main()
{
    createAndLaunchResource();
}
