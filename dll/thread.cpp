#define UNICODE
#include <Windows.h>
#include <iostream>
#include "thread.hpp"

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

[[noreturn]] void DynamicDefense()
{
    std::cout << "Performing dynamic checks.\n";
    // Launching the dynamic defense
    while (true)
    {
        // Do something
        hideThread(GetCurrentThread());
        checkWinDbg();
        debugWin32Check();
        checkHardwareBreakpoints();
        debugObjectCheck();
        Sleep(500);
    }
}

void checkWinDbg()
{
    HANDLE hWinDbg = FindWindow(TEXT("WinDbgFrameClass"), nullptr);

    if (hWinDbg)
    {
        std::cout << "Please close your debugging application and restart the program!\n";
        exit(1);
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