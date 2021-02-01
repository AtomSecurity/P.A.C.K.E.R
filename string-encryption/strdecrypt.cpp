#include "strdecrypt.hpp"

std::string stringDecrypt(std::string_view str)
{
    std::string ret{};

    for (size_t i{}; i < str.length(); ++i)
    {
        ret.push_back(str[i] ^ (i % 5));
    }

    return ret;
}