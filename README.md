# P.A.C.K.E.R


# Intro

P.A.C.K.E.R is a simple DRM software that can grant and verify serial keys, encrypt & decrypt [RSA & AES] your software. It also has modules to protect your executable (by injecting a thread and an attachable DLL) for anti-debugging purposes.
The code can be modified and used freely according to the MIT license.
 
## Server

The server authorizes user, generates authentication keys for user, writes the user's email and password to file, decrypts the key received from the client.
 
## P.A.C.K.E.R

Internal modules:
1. client.cpp (interactions with server; connections with server);
2. encrypt_rsa.cpp (encrypts data with public RSA key);
3. aes256encrypt.cpp (generates AES key, encrypts files "to_protect.exe, security.dll, thread.dll" with generated AES key); 
4. aes256decrypt.cpp (decrypts files);
5. aes256.cpp (contains AES256 implementation);
6. injector.cpp (injects "thread.dll" into the process of the application that is being launched);
7. loader.cpp (loads encrypted DLLs and protected file (to_protect.exe in our case) from the resources of the .exe file);
8. error.cpp (error wrapping);
9. resources.rc.
  
**Instead of "to_protect.exe", your executable can be used. If you want static defense, you can connect "security.dll" to your executable. If you want dynamic defense, you can leave it as it be, and thread.dll will automatically connect and do dynamic checks.** 

### String encription

This part is finished, but the project currently does not use it. Can be added to the P.A.C.K.E.R manually if you need it. 

# Software Requirements

**To compile** P.A.C.K.E.R you have to use Visual Studio x64 compiler (MSVC), OpenSSL library. The code is written and built in CLion. 
**To run** this project you need a Visual Studio Redistributable 2019 x64. OpenSSL Win64 library needs to be installed. 

# Download Visual Studio Redistributable 2019 x64, OpenSSL Win64 library

* OpenSSL https://slproweb.com/download/Win64OpenSSL-1_1_1k.exe
* VS Redist https://aka.ms/vs/16/release/vc_redist.x64.exe

# Download CLion and Visual Studio

* CLion https://www.jetbrains.com/clion/download/download-thanks.html?platform=windows
* VS https://visualstudio.microsoft.com/downloads/ (during the VS installation make sure to select the "Desktop development with C++" option)

# How to run

**Must be compiled for x64.**
 
* Build project according to the last instructions in CMakeLists:
	1. Comment the last line, begin with "add_executable(to-protect...";
	2. Enable auto-reload of the CMake project;
	3. Build the project for x64 platform;
	4. Uncomment the last line back;
	5. Rebuild, so it has the access to the DLL.

**Files "private.txt, public.txt" must be present in P.A.C.K.E.R\cmake-build-debug. "rsa.exe" can be used to generate them.** 

* In P.A.C.K.E.R folder run packer.exe and choose Encrypt your data (enter 2);
* Go to P.A.C.K.E.R\cmake-build-debug folder and copy these three files to P.A.C.K.E.R\resourses folder: to_protect.exe, thread.dll, security.dll;
* In CLion comment the last line in CMakeLists (as in the first step), rebuild, uncomment and build again;
* Finally, in P.A.C.K.E.R\cmake-build-debug run server, then packer and use it (enter 1).
 
If you did everything right, you should see the unpacked window. Otherwise, you did something wrong and have to repeat the instructions.
