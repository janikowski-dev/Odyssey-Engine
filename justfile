set shell := ["powershell.exe", "-NoLogo", "-NoProfile", "-Command"]

build-engine:
    powershell -ExecutionPolicy Bypass -File Commands/BuildEngine.ps1

clean-engine:
    powershell -ExecutionPolicy Bypass -File Commands/CleanEngine.ps1
