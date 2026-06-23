param(
    [Parameter(Mandatory = $true)]
    [string]$ProjectPath
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

cmd /c "`"$vsDevCmd`" && set" | ForEach-Object {
    if ($_ -match "=") {
        $name, $value = $_ -split "=", 2
        Set-Item -Path "env:$name" -Value $value
    }
}

Write-Host "MSVC environment loaded" -ForegroundColor Green

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