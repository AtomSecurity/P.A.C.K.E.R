cmake_minimum_required(VERSION 3.17)
project(P_A_C_K_E_R)

set(CMAKE_CXX_STANDARD 17)

# main file
add_executable(packer main.cpp loader/loader.cpp injector/injector.cpp resources/resources.rc error-wrapper/error.cpp)

# client-server
add_executable(client client-server/client.cpp)
add_executable(server client-server/server.cpp)

# strencrypt
add_executable(strencrypt string-encryption/strencrypt.cpp)

# security dll
add_library(security SHARED dll/security.cpp)

# file that we are trying to protect (comment, build, uncomment and build again so it has the access to the dll)
add_executable(to-protect to-protect/to-protect.cpp to-protect/to-protect.cpp)