set shell := ["powershell.exe", "-NoLogo", "-NoProfile", "-Command"]

build:
    powershell -ExecutionPolicy Bypass -File Commands/Build.ps1

clean:
    powershell -ExecutionPolicy Bypass -File Commands/Clean.ps1
