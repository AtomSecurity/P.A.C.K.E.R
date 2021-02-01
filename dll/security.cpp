#define UNICODE
#include <Windows.h>
#include <iostream>
#include "security.hpp"

void debugWin32Check()
{
    if (IsDebuggerPresent())
    {
        std::cout << "Please close your debugging application and restart the program!\n";
        exit(1);
    }
}

void checkHardwareBreakpoints()
{
    unsigned int NumBps {};

    // This structure is key to the function and is the
    // medium for detection and removal
    CONTEXT ctx;
    ZeroMemory(&ctx, sizeof(CONTEXT));

    // The CONTEXT structure is an in/out parameter therefore we have
    // to set the flags so Get/SetThreadContext knows what to set or get.
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

    // Get a handle to our thread
    HANDLE hThread {GetCurrentThread()};

    // Get the registers
    if (GetThreadContext(hThread, &ctx) == 0)
    {
        std::cout << "Can't access the registers. Quitting.\n";
        exit(1);
    }

    // Now we can check for hardware breakpoints, its not
    // necessary to check Dr6 and Dr7, however feel free to
    if(ctx.Dr0 != 0)
        ++NumBps;
    if(ctx.Dr1 != 0)
        ++NumBps;
    if(ctx.Dr2 != 0)
        ++NumBps;
    if(ctx.Dr3 != 0)
        ++NumBps;
    if(ctx.Dr6 != 0)
        ++NumBps;
    if(ctx.Dr7 != 0)
        ++NumBps;

    if (NumBps != 0)
    {
        std::cout << "Hardware breakpoints detected. Quitting.\n";
        exit(1);
    }
}

void debugObjectCheck()
{
    // Much easier in ASM but C/C++ looks so much better
    typedef NTSTATUS (WINAPI *pNtQueryInformationProcess)
            (HANDLE ,UINT ,PVOID ,ULONG , PULONG);

    HANDLE hDebugObject {nullptr};
    NTSTATUS Status;

    // Get NtQueryInformationProcess
    auto NtQIP = (pNtQueryInformationProcess)
            GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")),
                             "NtQueryInformationProcess");

    Status = NtQIP(GetCurrentProcess(),
                   0x1e, // ProcessDebugObjectHandle
                   &hDebugObject, 4, nullptr);

    if (Status != 0x00000000)
    {
        return;
    }

    if (hDebugObject)
    {
        std::cout << "Please close your debugging application and restart the program!\n";
        exit(1);
    }
}

void hideThread(HANDLE hThread)
{
    typedef NTSTATUS (NTAPI *pNtSetInformationThread)
            (HANDLE, UINT, PVOID, ULONG);
    NTSTATUS Status;

    // Get NtSetInformationThread
    auto NtSIT = (pNtSetInformationThread)
            GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")),
                           "NtSetInformationThread");

    // Shouldn't fail
    if (NtSIT == nullptr)
    {
        std::cout << "Can't access NtSIT. Quitting.\n";
        exit(1);
    }

    // Set the thread info
    if (hThread == nullptr)
    {
        Status = NtSIT(GetCurrentThread(),
                       0x11, // HideThreadFromDebugger
                       nullptr, 0);
    }
    else
    {
        Status = NtSIT(hThread, 0x11, nullptr, 0);
    }

    if (Status != 0x00000000)
    {
        std::cout << "Failed to hide.\n";
        exit(1);
    }
}

EXPORT void CALLBACK StaticDefense()
{
    std::cout << "Performing static checks.\n";
    // Launching the passive defense
    hideThread(GetCurrentThread());
    debugWin32Check();
    checkHardwareBreakpoints();
    debugObjectCheck();
    Sleep(1000);
}

bool isThreadSigned()
{
    // Check the thread somehow? Maybe connect to server, generate unique id and check it?
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
            // Need to delete the .dll and .exe from temp folder!
            exit(0);

        default:
            std::cout << "Something strange happened.\n";
            exit(1);
    }
    return TRUE;
}