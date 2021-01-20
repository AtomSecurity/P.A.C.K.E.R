cmake_minimum_required(VERSION 3.17)
project(P_A_C_K_E_R)

set(CMAKE_CXX_STANDARD 17)

add_executable(P_A_C_K_E_R main.cpp)
configure_file(resources/exe.rc resources/exe.rc)
add_executable(loader loader.cpp resources/exe.rc)
add_executable(client nasta_cia/client.cpp)
add_executable(server nasta_cia/server.cpp)