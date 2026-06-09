$configPath = Join-Path $PSScriptRoot "../Config.json"

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

cmake --preset default

if ($LASTEXITCODE -ne 0) {
    Write-Host "Configure failed" -ForegroundColor Red
    exit $LASTEXITCODE
}

cmake --build --preset default

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed" -ForegroundColor Red
    exit $LASTEXITCODE
}

Write-Host "Build successful" -ForegroundColor Green
