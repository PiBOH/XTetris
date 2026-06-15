[CmdletBinding()]
param(
    [string]$RepoUrl = "https://github.com/PiBOH/XTetris.git",
    [string]$RepoDir = "",
    [switch]$RunAfterBuild
)

$ErrorActionPreference = 'Stop'
$ScriptVersion = '1.0.9k-STABLE'
$script:SelfPath = $MyInvocation.MyCommand.Path
$script:LogDir = Join-Path $PSScriptRoot 'log'
$script:StateFile = Join-Path $script:LogDir 'installed-packages.txt'
$script:TranscriptStarted = $false
$script:LogFile = $null

function Ensure-LogInfrastructure {
    if (-not (Test-Path $script:LogDir)) {
        New-Item -ItemType Directory -Path $script:LogDir -Force | Out-Null
    }

    if (-not (Test-Path $script:StateFile)) {
        New-Item -ItemType File -Path $script:StateFile -Force | Out-Null
    }
}

function Initialize-Log {
    Ensure-LogInfrastructure
    $timestamp = Get-Date -Format 'yyyyMMdd-HHmmss'
    $script:LogFile = Join-Path $script:LogDir ("install-{0}.log" -f $timestamp)
    try {
        Start-Transcript -Path $script:LogFile -Force | Out-Null
        $script:TranscriptStarted = $true
    }
    catch {
        Write-WarnMsg "Impossibile avviare il transcript di log: $($_.Exception.Message)"
    }
}

function Finalize-Log {
    if ($script:TranscriptStarted) {
        try {
            Stop-Transcript | Out-Null
        }
        catch {
        }
        $script:TranscriptStarted = $false
    }
}

function Add-InstalledByScriptPackage([string]$Id) {
    Ensure-LogInfrastructure
    $entries = @()
    if (Test-Path $script:StateFile) {
        $entries = @(Get-Content -Path $script:StateFile -ErrorAction SilentlyContinue)
    }

    if ($entries -notcontains $Id) {
        Add-Content -Path $script:StateFile -Value $Id
    }
}

function Remove-InstalledByScriptPackage([string]$Id) {
    Ensure-LogInfrastructure
    if (-not (Test-Path $script:StateFile)) {
        return
    }

    $entries = @(Get-Content -Path $script:StateFile -ErrorAction SilentlyContinue | Where-Object { $_ -and $_ -ne $Id })
    Set-Content -Path $script:StateFile -Value $entries
}

function Test-InstalledByScriptPackage([string]$Id) {
    Ensure-LogInfrastructure
    if (-not (Test-Path $script:StateFile)) {
        return $false
    }

    $entries = @(Get-Content -Path $script:StateFile -ErrorAction SilentlyContinue)
    return ($entries -contains $Id)
}

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
    Add-PathIfExists "$env:ProgramFiles\PowerShell\7"
    Add-PathIfExists "$env:ProgramFiles\PowerShell\7-preview"
    Add-PathIfExists "$env:LOCALAPPDATA\Programs\Git\cmd"
    Add-PathIfExists "$env:LOCALAPPDATA\Programs\CMake\bin"
    Add-PathIfExists "$env:LOCALAPPDATA\Microsoft\WindowsApps"
    Add-PathIfExists "C:\msys64\ucrt64\bin"
    Add-PathIfExists "C:\msys64\usr\bin"
    Add-PathIfExists "$env:LOCALAPPDATA\Programs\MSYS2\ucrt64\bin"
    Add-PathIfExists "$env:LOCALAPPDATA\Programs\MSYS2\usr\bin"
    Add-PathIfExists "$env:ProgramFiles\MSYS2\ucrt64\bin"
    Add-PathIfExists "$env:ProgramFiles\MSYS2\usr\bin"
}

function Ensure-Winget {
    if (-not (Get-Command winget -ErrorAction SilentlyContinue)) {
        throw "winget non e disponibile. Installa 'App Installer' dal Microsoft Store e rilancia lo script."
    }
}

function Get-PwshPath {
    Refresh-CommonPaths

    $cmd = Get-Command pwsh -ErrorAction SilentlyContinue
    if ($cmd -and $cmd.Source) {
        return $cmd.Source
    }

    $candidates = @(
        "$env:ProgramFiles\PowerShell\7\pwsh.exe",
        "$env:ProgramFiles\PowerShell\7-preview\pwsh.exe",
        "$env:LOCALAPPDATA\Microsoft\WindowsApps\pwsh.exe"
    )

    foreach ($candidate in $candidates) {
        if (Test-Path $candidate) {
            return $candidate
        }
    }

    return $null
}

function Test-IsPowerShell7 {
    return ($PSVersionTable.PSEdition -eq 'Core' -and $PSVersionTable.PSVersion.Major -ge 7)
}

function New-ScriptArgumentList {
    $arguments = @(
        '-NoProfile',
        '-ExecutionPolicy', 'Bypass',
        '-File', $script:SelfPath,
        '-RepoUrl', $RepoUrl
    )

    if (-not [string]::IsNullOrWhiteSpace($RepoDir)) {
        $arguments += @('-RepoDir', $RepoDir)
    }

    if ($RunAfterBuild) {
        $arguments += '-RunAfterBuild'
    }

    return $arguments
}

function Ensure-PowerShell7Host {
    if (Test-IsPowerShell7) {
        return
    }

    Write-Step 'Rilevato Windows PowerShell classico: rilancio con PowerShell 7'

    $pwsh = Get-PwshPath
    if (-not $pwsh) {
        Ensure-Winget
        Write-Step 'PowerShell 7 non trovato: installo Microsoft.PowerShell con winget'
        winget install --id Microsoft.PowerShell --exact --accept-package-agreements --accept-source-agreements --disable-interactivity
        if ($LASTEXITCODE -ne 0) {
            throw 'Installazione di PowerShell 7 fallita.'
        }
        Add-InstalledByScriptPackage 'Microsoft.PowerShell'
        $pwsh = Get-PwshPath
    }

    if (-not $pwsh) {
        throw 'PowerShell 7 risulta installato ma pwsh.exe non e stato trovato.'
    }

    $arguments = New-ScriptArgumentList
    & $pwsh @arguments
    exit $LASTEXITCODE
}

function Test-WingetPackageInstalled([string]$Id) {
    $output = winget list --id $Id --exact --accept-source-agreements 2>$null | Out-String
    return ($output -match [regex]::Escape($Id))
}

function Ensure-WingetPackage([string]$Id, [string]$DisplayName) {
    if (Test-WingetPackageInstalled $Id) {
        Write-Ok "$DisplayName e gia installato"
        return
    }

    Write-Step "Installo $DisplayName con winget"
    winget install --id $Id --exact --accept-package-agreements --accept-source-agreements --disable-interactivity

    if (-not (Test-WingetPackageInstalled $Id)) {
        throw "Installazione di $DisplayName non riuscita o non rilevata correttamente."
    }

    Add-InstalledByScriptPackage $Id
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

function Ensure-PortableNotepad([string]$ProjectRoot) {
    $portableExe = Join-Path $ProjectRoot 'piboh-portable\Notepad++Portable\notepad++.exe'
    if (Test-Path $portableExe) {
        Write-Ok "Notepad++ Portable disponibile: $portableExe"
        return
    }

    Write-WarnMsg 'Notepad++ Portable non trovato nel repository.'
}

function Write-GameLauncher([string]$ProjectRoot) {
    $launcherPath = Join-Path $ProjectRoot 'AVVIA GIOCO.bat'
    $content = @"
@echo off
setlocal
chcp 65001 >nul 2>nul
set "LOG_DIR=%~dp0piboh-script\log"
if not exist "%LOG_DIR%" mkdir "%LOG_DIR%" >nul 2>nul
>> "%LOG_DIR%\avvia-gioco.log" echo [%date% %time%] Avvio launcher generato
cd /d "%~dp0"
if not exist "build\XTetris.exe" (
  echo.
  echo ERRORE: impossibile trovare build\XTetris.exe
  >> "%LOG_DIR%\avvia-gioco.log" echo [%date% %time%] ERRORE: build\XTetris.exe non trovato
  pause
  exit /b 1
)

echo Avvio XTetris...
"build\XTetris.exe"
set "EXITCODE=%ERRORLEVEL%"
>> "%LOG_DIR%\avvia-gioco.log" echo [%date% %time%] Fine launcher generato con exit code %EXITCODE%
echo.
pause
exit /b %EXITCODE%
REM Versione launcher generato: $ScriptVersion
REM File Generato con Arena AI (https://arena.ai/)
"@
    Set-Content -Path $launcherPath -Value $content -Encoding UTF8
    Write-Ok "Creato launcher: $launcherPath"
}

function Ask-YesNo([string]$Prompt, [bool]$DefaultYes = $true) {
    $suffix = if ($DefaultYes) { '[S/n]' } else { '[s/N]' }
    $answer = Read-Host "$Prompt $suffix"

    if ([string]::IsNullOrWhiteSpace($answer)) {
        return $DefaultYes
    }

    switch -Regex ($answer.Trim()) {
        '^(s|si|sì|y|yes)$' { return $true }
        '^(n|no)$' { return $false }
        default { return $DefaultYes }
    }
}

Refresh-CommonPaths
Ensure-PowerShell7Host
Refresh-CommonPaths
Initialize-Log

Write-Host "XTetris Windows Installer $ScriptVersion" -ForegroundColor Magenta

$principal = New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())
$adminRole = [Security.Principal.WindowsBuiltInRole]::Administrator
if (-not $principal.IsInRole($adminRole)) {
    Write-WarnMsg 'Non stai eseguendo lo script come amministratore. In molti casi va bene lo stesso, ma alcuni installer potrebbero chiedere conferma o fallire.'
}

Write-Step 'Verifico winget'
Ensure-Winget
Write-Ok 'winget disponibile'

Ensure-WingetPackage 'Microsoft.PowerShell' 'PowerShell 7'
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
        throw "La cartella '$repoDirResolved' non sembra contenere XTetris ed e gia popolata. Specifica -RepoDir con una cartella vuota o il repo corretto."
    }

    if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
        Refresh-CommonPaths
    }
    if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
        throw "Git non e disponibile nel PATH anche dopo l'installazione."
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
    Write-Ok 'Repository XTetris gia presente'
}

Ensure-PortableNotepad -ProjectRoot $repoDirResolved

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

Write-GameLauncher -ProjectRoot $repoDirResolved

$shouldRun = $RunAfterBuild -or (Ask-YesNo 'Vuoi avviare il gioco?')
if ($shouldRun) {
    Write-Step 'Avvio XTetris'
    & $exePath
}

Finalize-Log

# Versione script: 1.0.9k-STABLE
# File Generato con Arena AI (https://arena.ai/)
