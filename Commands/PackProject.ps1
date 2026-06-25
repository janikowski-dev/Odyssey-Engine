param(
    [Parameter(Mandatory = $true)]
    [string]$ProjectPath,

    [Parameter(Mandatory = $true)]
    [string]$OutputDir
)

Write-Host "Packing to: $OutputDir" -ForegroundColor Cyan

$launcherSrc = Join-Path $ProjectPath "Build/Launcher/Launcher.exe"
$levelSrc = Join-Path $ProjectPath "Level.odyscene"
$settingsSrc = Join-Path $ProjectPath "Launch.odysettings"
$resourcesSrc = Join-Path $ProjectPath "Resources"

$missing = @()
foreach ($p in @($launcherSrc, $levelSrc, $settingsSrc, $resourcesSrc)) {
    if (!(Test-Path $p)) { $missing += $p }
}
if ($missing.Count -gt 0) {
    Write-Host "Missing required files/folders:" -ForegroundColor Red
    $missing | ForEach-Object { Write-Host "  $_" -ForegroundColor Red }
    exit 1
}

try {
    $settings = Get-Content $settingsSrc -Raw | ConvertFrom-Json
}
catch {
    Write-Host "Failed to parse Launch.odysettings: $_" -ForegroundColor Red
    exit 1
}

$projectName = $settings.ProjectName
if ([string]::IsNullOrWhiteSpace($projectName)) {
    Write-Host "ProjectName is missing or empty in Launch.odysettings" -ForegroundColor Red
    exit 1
}

if (!(Test-Path $OutputDir)) {
    New-Item -ItemType Directory -Path $OutputDir -Force | Out-Null
}

$launcherDst = Join-Path $OutputDir "$projectName.exe"
Copy-Item -Path $launcherSrc -Destination $launcherDst -Force
Write-Host "Copied launcher -> $projectName.exe" -ForegroundColor Green

Copy-Item -Path $levelSrc    -Destination $OutputDir -Force
Copy-Item -Path $settingsSrc -Destination $OutputDir -Force
Write-Host "Copied Level.odyscene and Launch.odysettings" -ForegroundColor Green

$resourcesDst = Join-Path $OutputDir "Resources"
if (!(Test-Path $resourcesDst)) {
    New-Item -ItemType Directory -Path $resourcesDst -Force | Out-Null
}
Copy-Item -Path (Join-Path $resourcesSrc "*") -Destination $resourcesDst -Recurse -Force
Write-Host "Copied Resources contents" -ForegroundColor Green

Write-Host "Package complete -> $OutputDir" -ForegroundColor Green