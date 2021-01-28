#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <Windows.h>
#define EXPORT extern "C++" __declspec (dllexport)
EXPORT void CALLBACK StaticDefense();
bool isThreadSigned();

#endif //SECURITY_HPP