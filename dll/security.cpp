#define UNICODE
#include <Windows.h>
#include "security.hpp"

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, PVOID lpReserved)
{
    return TRUE;
}

EXPORT std::string CALLBACK GetCodeWord()
{
    std::string codeWord {"cr7pt0pl4gu3"};
    return codeWord;
}