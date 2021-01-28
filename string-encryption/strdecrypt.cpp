#include "strdecrypt.hpp"

std::string stringDecrypt(std::string_view str)
{
    std::string ret{};
    std::string numbers {"0123456789"};

    for (size_t i{}; i < str.length(); ++i)
    {
        if (numbers.find(str[i]) != std::string::npos)
        {
            ret.push_back(str[i]);
            continue;
        }
        ret.push_back(str[i] ^ (i % 5));
    }

    return ret;
}