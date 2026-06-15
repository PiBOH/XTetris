[CmdletBinding()]
param(
    [string]$RepoUrl = "https://github.com/PiBOH/XTetris.git",
    [string]$RepoDir = "",
    [switch]$RunAfterBuild
)

$ErrorActionPreference = 'Stop'

function Write-Step($Message) {
    Write-Host "`n==> $Message" -ForegroundColor Cyan
}

function Write-Ok($Message) {
    Write-Host "[OK] $Message" -ForegroundColor Green
}

function Write-WarnMsg($Message) {
    Write-Host "[WARN] $Message" -ForegroundColor Yellow
}

function Add-PathIfExists([string]$PathToAdd) {
    if ([string]::IsNullOrWhiteSpace($PathToAdd)) { return }
    if (-not (Test-Path $PathToAdd)) { return }

    $current = ($env:PATH -split ';') | Where-Object { $_ -ne '' }
    if ($current -notcontains $PathToAdd) {
        $env:PATH = "$PathToAdd;$env:PATH"
    }
}

function Refresh-CommonPaths {
    Add-PathIfExists "$env:ProgramFiles\Git\cmd"
    Add-PathIfExists "$env:ProgramFiles\CMake\bin"
    Add-PathIfExists "$env:LOCALAPPDATA\Programs\Git\cmd"
    Add-PathIfExists "$env:LOCALAPPDATA\Programs\CMake\bin"
    Add-PathIfExists "C:\msys64\ucrt64\bin"
    Add-PathIfExists "C:\msys64\usr\bin"
    Add-PathIfExists "$env:LOCALAPPDATA\Programs\MSYS2\ucrt64\bin"
    Add-PathIfExists "$env:LOCALAPPDATA\Programs\MSYS2\usr\bin"
    Add-PathIfExists "$env:ProgramFiles\MSYS2\ucrt64\bin"
    Add-PathIfExists "$env:ProgramFiles\MSYS2\usr\bin"
}

function Ensure-Winget {
    if (-not (Get-Command winget -ErrorAction SilentlyContinue)) {
        throw "winget non è disponibile. Installa 'App Installer' dal Microsoft Store e rilancia lo script."
    }
}

function Test-WingetPackageInstalled([string]$Id) {
    $output = winget list --id $Id --exact --accept-source-agreements 2>$null | Out-String
    return ($output -match [regex]::Escape($Id))
}

function Ensure-WingetPackage([string]$Id, [string]$DisplayName) {
    if (Test-WingetPackageInstalled $Id) {
        Write-Ok "$DisplayName è già installato"
        return
    }

    Write-Step "Installo $DisplayName con winget"
    winget install --id $Id --exact --accept-package-agreements --accept-source-agreements

    if (-not (Test-WingetPackageInstalled $Id)) {
        throw "Installazione di $DisplayName non riuscita o non rilevata correttamente."
    }

    Write-Ok "$DisplayName installato"
}

function Find-Msys2Root {
    $candidates = @(
        'C:\msys64',
        "$env:LOCALAPPDATA\Programs\MSYS2",
        "$env:ProgramFiles\MSYS2"
    )

    foreach ($candidate in $candidates) {
        if (Test-Path (Join-Path $candidate 'usr\bin\bash.exe')) {
            return $candidate
        }
    }

    throw "MSYS2 non trovato. Verifica che l'installazione sia andata a buon fine."
}

function Convert-ToMsysPath([string]$WindowsPath) {
    $full = [System.IO.Path]::GetFullPath($WindowsPath)
    $normalized = $full.Replace('\', '/')

    if ($normalized -match '^([A-Za-z]):/(.*)$') {
        $drive = $matches[1].ToLower()
        $rest = $matches[2]
        return "/$drive/$rest"
    }

    throw "Impossibile convertire il path per MSYS2: $WindowsPath"
}

function Invoke-MsysBash {
    param(
        [Parameter(Mandatory = $true)] [string]$MsysRoot,
        [Parameter(Mandatory = $true)] [string]$Command,
        [string]$WorkingDirectory = ''
    )

    $bash = Join-Path $MsysRoot 'usr\bin\bash.exe'
    if (-not (Test-Path $bash)) {
        throw "bash.exe non trovato in MSYS2"
    }

    $env:CHERE_INVOKING = '1'
    $env:MSYSTEM = 'UCRT64'
    $env:MSYS2_PATH_TYPE = 'inherit'

    if ($WorkingDirectory) {
        $msysPath = Convert-ToMsysPath $WorkingDirectory
        $wrapped = "cd '$msysPath' && $Command"
    }
    else {
        $wrapped = $Command
    }

    & $bash -lc $wrapped
    if ($LASTEXITCODE -ne 0) {
        throw "Comando MSYS2 fallito con exit code $LASTEXITCODE"
    }
}

function Resolve-RepoDir([string]$ProvidedDir) {
    $scriptDir = Split-Path -Parent $PSCommandPath
    $repoCandidate = Split-Path -Parent $scriptDir
    $currentDir = (Get-Location).Path

    if (-not [string]::IsNullOrWhiteSpace($ProvidedDir)) {
        return [System.IO.Path]::GetFullPath($ProvidedDir)
    }

    if (Test-Path (Join-Path $currentDir 'CMakeLists.txt')) {
        return [System.IO.Path]::GetFullPath($currentDir)
    }

    if (Test-Path (Join-Path $scriptDir 'CMakeLists.txt')) {
        return [System.IO.Path]::GetFullPath($scriptDir)
    }

    if (Test-Path (Join-Path $repoCandidate 'CMakeLists.txt')) {
        return [System.IO.Path]::GetFullPath($repoCandidate)
    }

    return [System.IO.Path]::GetFullPath((Join-Path $currentDir 'XTetris'))
}

Refresh-CommonPaths

$principal = New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())
$adminRole = [Security.Principal.WindowsBuiltInRole]::Administrator
if (-not $principal.IsInRole($adminRole)) {
    Write-WarnMsg 'Non stai eseguendo lo script come amministratore. In molti casi va bene lo stesso, ma alcuni installer potrebbero chiedere conferma o fallire.'
}

Write-Step 'Verifico winget'
Ensure-Winget
Write-Ok 'winget disponibile'

Ensure-WingetPackage 'Git.Git' 'Git'
Ensure-WingetPackage 'Kitware.CMake' 'CMake'
Ensure-WingetPackage 'MSYS2.MSYS2' 'MSYS2'

Refresh-CommonPaths

$repoDirResolved = Resolve-RepoDir $RepoDir
Write-Step "Cartella di lavoro: $repoDirResolved"

if (-not (Test-Path $repoDirResolved)) {
    New-Item -ItemType Directory -Path $repoDirResolved | Out-Null
}

if (-not (Test-Path (Join-Path $repoDirResolved 'CMakeLists.txt'))) {
    $items = @(Get-ChildItem -Force -Path $repoDirResolved -ErrorAction SilentlyContinue)
    if ($items.Count -gt 0 -and -not (Test-Path (Join-Path $repoDirResolved '.git'))) {
        throw "La cartella '$repoDirResolved' non sembra contenere XTetris ed è già popolata. Specifica -RepoDir con una cartella vuota o il repo corretto."
    }

    if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
        Refresh-CommonPaths
    }
    if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
        throw "Git non è disponibile nel PATH anche dopo l'installazione."
    }

    if (-not (Test-Path (Join-Path $repoDirResolved '.git'))) {
        Write-Step 'Clono il repository XTetris'
        git clone $RepoUrl $repoDirResolved
        if ($LASTEXITCODE -ne 0) {
            throw 'git clone fallito'
        }
        Write-Ok 'Repository clonato'
    }
}
else {
    Write-Ok 'Repository XTetris già presente'
}

$msysRoot = Find-Msys2Root
Write-Ok "MSYS2 trovato in $msysRoot"

Write-Step 'Installo toolchain e strumenti di build in MSYS2 (UCRT64)'
Invoke-MsysBash -MsysRoot $msysRoot -Command @'
set -e
pacman -Sy --noconfirm
pacman -S --noconfirm --needed \
  mingw-w64-ucrt-x86_64-gcc \
  mingw-w64-ucrt-x86_64-cmake \
  mingw-w64-ucrt-x86_64-ninja
'@
Write-Ok 'Toolchain installata'

Write-Step 'Configuro e compilo XTetris'
Invoke-MsysBash -MsysRoot $msysRoot -WorkingDirectory $repoDirResolved -Command @'
set -e
export PATH="/ucrt64/bin:$PATH"
cmake -S . -B build -G Ninja
cmake --build build
'@

$exePath = Join-Path $repoDirResolved 'build\XTetris.exe'
if (-not (Test-Path $exePath)) {
    throw "Build completata ma eseguibile non trovato: $exePath"
}

Write-Ok "Build completata: $exePath"
Write-Host "`nPer avviare il gioco:" -ForegroundColor Cyan
Write-Host "  $exePath" -ForegroundColor White

if ($RunAfterBuild) {
    Write-Step 'Avvio XTetris'
    & $exePath
}

# File Generato con Arena AI (https://arena.ai/)
