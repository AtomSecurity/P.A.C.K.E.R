cmake_minimum_required(VERSION 3.17)
project(P_A_C_K_E_R)

set(CMAKE_CXX_STANDARD 17)

add_executable(P_A_C_K_E_R main.cpp)
add_executable(loader loader.cpp)
add_executable(activator nasta_cia/activator.cpp)
add_executable(keygen nasta_cia/keygen.cpp)