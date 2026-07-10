param(
    [Parameter(Mandatory = $true)]
    [string]$ProjectPath,

    [Parameter(Mandatory = $true)]
    [string]$CallerPath
)

$configPath = Join-Path $PSScriptRoot "../justconfig.json"

if (!(Test-Path $configPath)) {
    Write-Host "Config file not found: $configPath" -ForegroundColor Red
    exit 1
}

$config = Get-Content $configPath | ConvertFrom-Json
$vsDevCmd = $config.vsDevCmd

if (!(Test-Path $vsDevCmd)) {
    Write-Host "VsDevCmd not found!" -ForegroundColor Red
    exit 1
}

cmd /c "`"$vsDevCmd`" -arch=x64 -host_arch=x64 && set" | ForEach-Object {
    if ($_ -match "^([^=]+)=(.*)$") {
        Set-Item -Path "env:$($matches[1])" -Value $matches[2]
    }
}

Write-Host "MSVC environment loaded" -ForegroundColor Green

$env:ODYSSEY_ENGINE_ROOT = (Resolve-Path (Join-Path $CallerPath  "/Engine")).Path

Push-Location (Join-Path $ProjectPath "Source")

cmake --preset default

if ($LASTEXITCODE -ne 0) {
    Write-Host "Configure failed" -ForegroundColor Red
    Pop-Location
    exit $LASTEXITCODE
}

cmake --build --preset default

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed" -ForegroundColor Red
    Pop-Location
    exit $LASTEXITCODE
}

Pop-Location

Write-Host "Build successful" -ForegroundColor Green