#include <iostream>

// #include "client.hpp"
#include "loader.hpp"

int main()
{
    std::cout << "Welcome to P.A.C.K.E.R!" << std::endl;
    loadResource();
    /*
    if (activateLicense())
    {
        loadResource();
    }
    else
    {
        return 1;
    }
    */
    std::cout << "You can close this window now." << std::endl;
}
