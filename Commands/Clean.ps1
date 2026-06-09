Write-Host "Cleaning build..." -ForegroundColor Yellow

cmake --build --preset default --target clean

if ($LASTEXITCODE -ne 0) {
    Write-Host "Clean failed" -ForegroundColor Red
    exit $LASTEXITCODE
}

Write-Host "Clean complete" -ForegroundColor Green
