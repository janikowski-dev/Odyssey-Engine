param(
    [Parameter(Mandatory = $true)]
    [string]$ProjectParentPath,

    [Parameter(Mandatory = $true)]
    [string]$ProjectName
)

$templatePath = Join-Path $PSScriptRoot "../Template"
$destination = Join-Path $ProjectParentPath $ProjectName

if (-not (Test-Path $templatePath)) {
    Write-Error "Template not found at: $templatePath"
    exit 1
}

if (Test-Path $destination) {
    Write-Error "Destination already exists: $destination"
    exit 1
}

New-Item -ItemType Directory -Path $destination | Out-Null
Copy-Item -Path (Join-Path $templatePath '*') -Destination $destination -Recurse
Write-Host "Created project at: $destination"