/*STRDECRYPT by cr7pt0pl4gu3.*/

#include <string>

std::string stringDecrypt(std::string str) {
    std::string ret{};

    for (size_t i{}; i < str.length(); ++i)
    {
        ret.push_back(str[i] ^ (i % 10));
    }

    return ret;
}