Write-Host "Cleaning build..." -ForegroundColor Yellow

$enginePath = Join-Path $PSScriptRoot "../Engine"

if (!(Test-Path $enginePath)) {
    Write-Host "Engine directory not found: $enginePath" -ForegroundColor Red
    exit 1
}

Push-Location $enginePath

cmake --build --preset default --target clean

if ($LASTEXITCODE -ne 0) {
    Write-Host "Clean failed" -ForegroundColor Red
    Pop-Location
    exit $LASTEXITCODE
}

Pop-Location

Write-Host "Clean complete" -ForegroundColor Green