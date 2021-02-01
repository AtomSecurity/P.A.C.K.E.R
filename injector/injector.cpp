/* ThreadInjector by cr7pt0pl4gu3. */

#define UNICODE
#include <Windows.h>
#include <iostream>
#include <filesystem>
#include "../resources/resources.hpp"
#include "../error-wrapper/error.hpp"

void injectThread(int pid)
{

    // Opening a handle to the process
    HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD, FALSE, pid);
    if (!hProcess)
    {
        Error("Unable to open a handle to the target process!\n");
    }

    // Allocating memory in the target process for future .dll injection
    void *buffer = VirtualAllocEx(hProcess, nullptr, 1 << 12, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!buffer)
    {
        Error("Failed to allocate memory in the target process!\n");
    }

    // Hardcoded path to the security .dll
    std::string path {std::filesystem::temp_directory_path().string().append("security.dll")};

    // Writing .dll to the target process memory
    if (!WriteProcessMemory(hProcess, buffer, &path, path.length(), nullptr))
    {
        Error("Failed to write .dll in the target process memory!\n");
    }

    // Creating remote thread in the target .exe that we try to defend
    HANDLE hThread = CreateRemoteThread(hProcess, nullptr, 0,
                                        (LPTHREAD_START_ROUTINE)
                                                GetProcAddress(GetModuleHandle(L"kernel32"),"LoadLibraryA"),
                                        buffer, 0, nullptr);
    if (!hThread)
    {
        Error("Failed to create remote thread!\n");
    }
}