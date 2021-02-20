cmake_minimum_required(VERSION 3.17)
project(P_A_C_K_E_R)

# setting С++ 17 standard
set(CMAKE_CXX_STANDARD 17)

include_directories("C:/Program Files/OpenSSL-Win64/include")
link_directories("C:/Program Files/OpenSSL-Win64/lib")

# main file
add_executable(packer main.cpp loader/loader.cpp injector/injector.cpp resources/resources.rc error-wrapper/error.cpp aes256/aes256encrypt.cpp aes256/aes256decrypt.cpp aes256/aes256.cpp)

# client-server
add_executable(client client-server/client.cpp rsa/encrypt_rsa.cpp)
add_executable(server client-server/server.cpp rsa/decrypt_rsa.cpp)
target_link_libraries(client libcrypto)
target_link_libraries(server libcrypto)

# strencrypt
add_executable(strencrypt string-encryption/strencrypt.cpp)

# security dll and thread dll
add_library(security SHARED dll/security.cpp)
add_library(thread SHARED dll/thread.cpp)

# rsa
add_executable(rsa rsa/generate_key_rsa.cpp rsa/encrypt_rsa.cpp rsa/decrypt_rsa.cpp)

# openssl
find_package(OpenSSL REQUIRED)
target_link_libraries(rsa PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# file that we are trying to protect (comment, build, uncomment and build again so it has the access to the dll)
add_executable(to-protect to-protect/to-protect.cpp to-protect/to-protect.cpp)