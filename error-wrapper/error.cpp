#include <iostream>
#include <Windows.h>

// Error wrapper that shows a string and an error code using GetLastError(), then exits
void Error(std::string_view msg)
{
    std::cout << msg << " (" << GetLastError() << ")";
    exit(1);
}