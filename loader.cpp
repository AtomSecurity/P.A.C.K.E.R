#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <Windows.h>

HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(10), RT_RCDATA);
HGLOBAL hGlob = LoadResource(NULL, hRes);

BYTE* pData = (BYTE*)LockResource(hGlob);

DWORD dwFileSize = SizeofResource(NULL, hRes);
int hFile = open("test.exe", O_BINARY | O_CREAT | O_WRONLY, S_IWRITE);