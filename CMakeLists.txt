cmake_minimum_required(VERSION 3.17)
project(P_A_C_K_E_R)

# setting С++ 17 standard
set(CMAKE_CXX_STANDARD 17)



# openssl
include_directories("C:/Program Files/OpenSSL-Win64/include")
link_directories("C:/Program Files/OpenSSL-Win64/lib")
find_package(OpenSSL REQUIRED)
set(OPENSSL_USE_STATIC_LIBS TRUE)

# packer main file
add_executable(packer main.cpp client-server/client.cpp rsa/encrypt_rsa.cpp loader/loader.cpp injector/injector.cpp resources/resources.rc error-wrapper/error.cpp aes256/aes256encrypt.cpp aes256/aes256decrypt.cpp aes256/aes256.cpp)

# client-server
# add_executable(client client-server/client.cpp rsa/encrypt_rsa.cpp)
#target_link_libraries(client libcrypto)
add_executable(server client-server/server.cpp rsa/decrypt_rsa.cpp)
target_link_libraries(server OpenSSL::Crypto)
target_link_libraries(packer OpenSSL::Crypto)

# strencrypt
add_executable(strencrypt string-encryption/strencrypt.cpp)

# security dll and thread dll
add_library(security SHARED dll/security.cpp)
add_library(thread SHARED dll/thread.cpp)

# rsa
# add_executable(rsa rsa/generate_key_rsa.cpp rsa/encrypt_rsa.cpp rsa/decrypt_rsa.cpp)
# target_link_libraries(rsa PRIVATE OpenSSL::Crypto)


# file that we are trying to protect (comment, build, uncomment and build again so it has the access to the dll)
add_executable(to-protect to-protect/to-protect.cpp to-protect/to-protect.cpp)