param(
    [string]$ProjectPath
)

dotnet build Editor/OdysseyEditor.sln
Start-Process "Editor\OdysseyEditor.UI\bin\Debug\net10.0-windows\OdysseyEditor.UI.exe" -ArgumentList $ProjectPath -NoNewWindow -Wait