# Download files
import requests
import os

# OpenSSL
url_openssl = 'https://slproweb.com/download/Win64OpenSSL-1_1_1k.exe'

r = requests.get(url_openssl)

with open("openssl.exe", "wb") as code:
    code.write(r.content)

os.startfile('openssl.exe')

# Visual Studio Redistributable 2019 x64
url_VSR = 'https://aka.ms/vs/16/release/vc_redist.x64.exe'

r = requests.get(url_VSR)

with open("visual_studio_redist.exe", "wb") as code:
    code.write(r.content)

os.startfile('visual_studio_redist.exe')
