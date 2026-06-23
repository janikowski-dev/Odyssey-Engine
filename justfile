set shell := ["powershell.exe", "-NoLogo", "-NoProfile", "-Command"]

run-editor project_path:
    powershell -ExecutionPolicy Bypass -File Commands/RunEditor.ps1 {{project_path}}

new-project parent name:
    powershell -ExecutionPolicy Bypass -File Commands/NewProject.ps1 {{parent}} {{name}}

build-project project_path:
    powershell -ExecutionPolicy Bypass -File Commands/BuildProject.ps1 "{{project_path}}"