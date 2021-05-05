# P.A.C.K.E.R
P.A.C.K.E.R is an advanced packer &amp; defense.

# Intro
Packer is a project which provides secure communications between Server and Client using RSA and AES encryption algorithms on the Windows platform. This is an Open Source project.
 
# Block description
 
## Server
The server authorizes user, generates authentication keys for user, writes the user's email and password to file, decrypts key, received from the client.
 
## Packer
Packer consists of a Client side that interacts with user for authentication and encrypts "to_protect.exe, security.dll, thread.dll" with AES.
Client's modules: 
	1. client.cpp (the main part of code, interaction with user; connection with server);
	2. encrypt_rsa.cpp (to encrypt data with RSA key);
	3. aes256encrypt.cpp (genetate AES key, encrypt files "to_protect.exe, security.dll, thread.dll" with generated AES key); 
	4. aes256decrypt.cpp (decrypt files);
	5. loader.cpp (loads encrypted DLLs and protected file(to_protect in our case) from the resources of the exe file);
	6. injector.cpp (inject "thread.dll" into the process of the application that is being launched);
	7. error.cpp (for good error wrapping);
	8. aes256.cpp (contains AES256 implementation).
	9. resources.rc
  
!!! Instead of "to_protect.exe", your executable can be used. If you want static defense, you can connect "security.dll" to your executable. If you want to dynamic defense, you can leave it as it be, and thread.dll will automatically connect and do dynamic checks  

# Software Requirements
To compile Packer you have to use Visual Studio x64 compiler (MSVC), OpenSSL library. This code is written and built in CLion. 
!!!Must be compiled with x64.
To run this project you need a Visual Studio Redistributable 2019 x64. OpenSSL Win64 library is used.
To automatically download OpenSSL Win64 Library and Visual Studio, 'downloader.py' can be used. (You need to install Python and )  

# How to run
 
!!!There must be such files in P.A.C.K.E.R\cmake-build-debug: private.txt, public.txt. "rsa.exe" can be used to generate them.
 
* Build project according to the last instructions in CMakeLists:
	1. Comment that the last line, begin with "add_executable(to-protect...";
	2. Build all project;
	3. Uncomment line;
	4. Rebuild, so it has the access to the DLL.
* In P.A.C.K.E.R folder run packer.exe and choose Encrypt your data(enter 2);
* Go to P.A.C.K.E.R\cmake-build-debug folder and copy these three files to P.A.C.K.E.R\resourses folder: to_protect.exe, thread.dll, security.dll;
* In CLion comment the last line in CMakeLists(as in the first step), rebuild, uncomment and build again;
* Finally, in P.A.C.K.E.R\cmake-build-debug run server, then packer and follow the instructions.
 
If you did everything right, you should see the unpacked window. Otherwise, you did something wrong and have to repeat the instructions.
