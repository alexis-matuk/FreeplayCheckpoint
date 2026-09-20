param(
    [ValidateSet("Release")]
    [string]$Configuration = "Release",
    [ValidateSet("x64")]
    [string]$Platform = "x64"
)

$ErrorActionPreference = "Stop"

$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (-not (Test-Path $vswhere)) {
    throw "Visual Studio Build Tools were not found. Install Visual Studio 2019 Build Tools with the C++ workload."
}

$msbuild = & $vswhere `
    -latest `
    -products * `
    -version "[16.0,17.0)" `
    -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
    -find "MSBuild\**\Bin\MSBuild.exe" |
    Select-Object -First 1

if (-not $msbuild) {
    throw "MSVC v142 was not found. Install Visual Studio 2019 Build Tools with the C++ workload."
}

$bakkesModPath = (Get-ItemProperty "HKCU:\Software\BakkesMod\AppPath" -ErrorAction SilentlyContinue).BakkesModPath
if (-not $bakkesModPath -or -not (Test-Path (Join-Path $bakkesModPath "bakkesmodsdk\lib\pluginsdk.lib"))) {
    throw "The BakkesMod SDK was not found. Start BakkesMod once and verify its SDK is installed."
}

$solution = Join-Path $PSScriptRoot "CheckpointPlugin.sln"
& $msbuild $solution `
    /t:Build `
    /p:Configuration=$Configuration `
    /p:Platform=$Platform `
    /m `
    /v:minimal `
    /nologo

if ($LASTEXITCODE -ne 0) {
    throw "Build failed with exit code $LASTEXITCODE."
}

$plugin = Join-Path $bakkesModPath "plugins\CheckpointPlugin.dll"
if (-not (Test-Path $plugin)) {
    throw "Build succeeded, but the BakkesMod patcher did not install the plugin."
}

Write-Host "Build and BakkesMod patch completed successfully: $plugin"
