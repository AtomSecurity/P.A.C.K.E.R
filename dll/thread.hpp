#ifndef THREAD_HPP
#define THREAD_HPP

void StaticDefense();
bool isThreadSigned();
void debugWin32Check();
void checkHardwareBreakpoints();
void debugObjectCheck();
void hideThread(HANDLE hThread);
void checkWinDbg();

#endif //THREAD_HPP