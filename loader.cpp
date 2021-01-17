#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <Windows.h>

int main()
{
    HRSRC hRes = FindResource(nullptr, MAKEINTRESOURCE(10), RT_RCDATA);
    HGLOBAL hGlob = LoadResource(nullptr, hRes);

    BYTE* pData = (BYTE*)LockResource(hGlob);

    DWORD dwFileSize = SizeofResource(nullptr, hRes);
    int hFile = open("test.exe", O_BINARY | O_CREAT | O_WRONLY);
}