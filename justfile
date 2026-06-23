set shell := ["powershell.exe", "-NoLogo", "-NoProfile", "-Command"]

build-engine:
    powershell -ExecutionPolicy Bypass -File Commands/BuildEngine.ps1

run-editor path:
    powershell -ExecutionPolicy Bypass -File Commands/RunEditor.ps1 {{path}}

new-project parent name:
    powershell -ExecutionPolicy Bypass -File Commands/NewProject.ps1 {{parent}} {{name}}

build-project path:
    powershell -ExecutionPolicy Bypass -File Commands/BuildProject.ps1 "{{path}}"

build-and-run path: (build-project path) (run-editor path)