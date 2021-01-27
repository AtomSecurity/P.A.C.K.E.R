/*STRENCRYPT by cr7pt0pl4gu3.*/

#include <iostream>
#include <string>

std::string stringEncrypt(std::string_view str)
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

int main()
{
    // Initializing our empty string
    std::string str {};

    // Prompting user for input and directing it to str
    std::cout << "STRENCRYPT by cr7pt0pl4gu3.\n\n" << "Enter your string below:\n";
    std::getline(std::cin, str);

    // Encrypting our string
    std::string encrypted {stringEncrypt(str)};

    // Returning encrypted string to our user
    std::cout << "\nHere is your encrypted string:\n" << encrypted << "\n\n";

    // Displaying final exit message
    std::cout << "Press Enter to exit application...\n";
    std::cin.get();
}