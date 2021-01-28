#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <string>

#define EXPORT extern "C++" __declspec (dllexport)
EXPORT std::string CALLBACK GetCodeWord();

#endif //SECURITY_HPP