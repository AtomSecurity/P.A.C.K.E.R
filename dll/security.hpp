#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <Windows.h>
#define EXPORT extern "C++" __declspec (dllexport)

EXPORT void CALLBACK StaticDefense();
bool isThreadSigned();
void debugWin32Check();
void checkHardwareBreakpoints();
void debugObjectCheck();
void hideThread(HANDLE hThread);
void checkWinDbg();

#endif //SECURITY_HPP