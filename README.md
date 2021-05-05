# P.A.C.K.E.R
P.A.C.K.E.R is an advanced packer &amp; defense.

# Intro
Packer is a project which provides secure communications between Server and Client using RSA and AES encryption algorithms on the Windows platform. This is an Open Source project.
 
# Block description
 
## Server
The server authorizes user, generates authentication keys for user, writes to file the user's email and password, decrypts key received from client.
 
## Packer
Packer is a Client side that interacts with user for authentication and encrypts "to_protect.exe, security.dll, thread.dll" with AES.
It consists of 9 modules:

1. client.cpp (the main part of code, interaction with user; connection with server);
2. encrypt_rsa.cpp (to encrypt data with RSA key);
3. aes256encrypt.cpp (genetate aes key, encrypt files "to_protect.exe, security.dll, thread.dll" with generated AES key); 
4. aes256decrypt.cpp (decrypt files);
5. loader.cpp (loads encrypted DLLs and protected file(to_protect in our case) from the resources of the exe file);
6. injector.cpp (inject "thread.dll" into the process of the application that is being launched);
7. error.cpp (for good error wrapping);
8. resources.rc
9. aes256.cpp (contains AES265 implementation).
  
!!! Instead of "to_protect.exe", your own executable can be used, but do some checks in  "security.dll".

# Software Requirements
To compile Packer you have to use Visual Studio x64 compiler (MSVC), OpenSSL library. This code is written and built CLion. 
!!!Obviously to compile for x64. (исправить)
To run this project it is needed a Visual Studio Redistributable 2019 x64. OpenSSL Win64 library is used. (исправить)
To automatically download OpenSSL Win64 Library and Visual Studio, `downloader.py` can be used.

# How to run
 
!!!There must be such files in P.A.C.K.E.R\cmake-build-debug: private.txt, public.txt. Check, if you do not have, use rsa.exe to generate.  №№(перефразировать)
 
0. Build project according to the last instructions in CMakeLists:
	1. Comment that last line, begin with "add_executable(to-protect...";
	2. Build all project;
	3. Uncomment line;
	4. Rebuild, so it has the access to the DLL.
0. In P.A.C.K.E.R folder run packer.exe and choose Encrypt your data(enter 2);
0. Go to P.A.C.K.E.R\cmake-build-debug folder and copy these three files to P.A.C.K.E.R\resourses folder: to_protect.exe, thread.dll, security.dll;
0. In CLion comment the last line in CMakeLists(as in the first step), rebuild, uncomment and build again;   (подробно расписать)
0. Finally, in P.A.C.K.E.R\cmake-build-debug run server, then packer and follow the instructions.
 
If you did everything right, you should see the unpacked window. Otherwise, you did something wrong and have to repeat the instructions.
