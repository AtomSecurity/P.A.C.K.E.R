# P.A.C.K.E.R


# Intro

 
## Server

The server authorizes user, generates authentication keys for user, writes the user's email and password to file, decrypts the key received from the client.
 
## Packer

Internal modules:
	1. client.cpp (the most of the code, interactions with server; connections with server);
	2. encrypt_rsa.cpp (encrypts data with public RSA key);
	3. aes256encrypt.cpp (generates AES key, encrypts files "to_protect.exe, security.dll, thread.dll" with generated AES key); 
	4. aes256decrypt.cpp (decrypts files);
	5. aes256.cpp (contains AES256 implementation);
	6. injector.cpp (injects "thread.dll" into the process of the application that is being launched);
	7. loader.cpp (loads encrypted DLLs and protected file(to_protect.exe in our case) from the resources of the .exe file);
	8. error.cpp (good error wrapping);
	9. resources.rc.
  
**Instead of "to_protect.exe", your executable can be used. If you want static defense, you can connect "security.dll" to your executable. If you want dynamic defense, you can leave it as it be, and thread.dll will automatically connect and do dynamic checks.** 

##String encription

This part is finished, but didn't add to the project. Can be added to the Packer. 

# Software Requirements

**To compile** Packer you have to use Visual Studio x64 compiler (MSVC), OpenSSL library. This code is written and built in CLion. 
**To run** this project you need a Visual Studio Redistributable 2019 x64. OpenSSL Win64 library is used. 

# Download Visual Studio Redistributable 2019 x64, OpenSSL Win64 library

* Install Python3
* Run "downloader.py"

# Download CLion and Visual Studio

* CLion https://www.jetbrains.com/clion/download/download-thanks.html?platform=windows
* VS https://visualstudio.microsoft.com/downloads/

# How to run

**Must be compiled with x64.**
 
* Build project according to the last instructions in CMakeLists:
	1. Comment that the last line, begin with "add_executable(to-protect...";
	2. Build all project for x64 platform;
	3. Uncomment the last line back;
	4. Rebuild, so it has the access to the DLL.

**Files "private.txt, public.txt" must be present in P.A.C.K.E.R\cmake-build-debug. "rsa.exe" can be used to generate them.** 

* In P.A.C.K.E.R folder run packer.exe and choose Encrypt your data(enter 2);
* Go to P.A.C.K.E.R\cmake-build-debug folder and copy these three files to P.A.C.K.E.R\resourses folder: to_protect.exe, thread.dll, security.dll;
* In CLion comment the last line in CMakeLists(as in the first step), rebuild, uncomment and build again;
* Finally, in P.A.C.K.E.R\cmake-build-debug run server, then packer and follow the instructions.
 
If you did everything right, you should see the unpacked window. Otherwise, you did something wrong and have to repeat the instructions.
