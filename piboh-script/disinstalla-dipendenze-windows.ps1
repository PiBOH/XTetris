[CmdletBinding()]
param(
    [string]$RepoDir = ""
)

$ErrorActionPreference = 'Stop'
$script:VersionFile = Join-Path $PSScriptRoot 'version.txt'
$ScriptVersion = if (Test-Path $script:VersionFile) { (Get-Content -Path $script:VersionFile -ErrorAction SilentlyContinue | Select-Object -First 1).Trim() } else { '0.0.0-UNKNOWN' }
$script:SelfPath = $MyInvocation.MyCommand.Path
$script:LogDir = Join-Path $PSScriptRoot 'log'
$script:StateFile = Join-Path $script:LogDir 'installed-packages.txt'
$script:StateMetaFile = Join-Path $script:LogDir 'installed-packages.csv'
$script:TranscriptStarted = $false
$script:LogFile = $null

function Ensure-LogInfrastructure {
    if (-not (Test-Path $script:LogDir)) {
        New-Item -ItemType Directory -Path $script:LogDir -Force | Out-Null
    }

    if (-not (Test-Path $script:StateFile)) {
        New-Item -ItemType File -Path $script:StateFile -Force | Out-Null
    }

    if (-not (Test-Path $script:StateMetaFile)) {
        New-Item -ItemType File -Path $script:StateMetaFile -Force | Out-Null
    }
}

function Initialize-Log {
    Ensure-LogInfrastructure
    $timestamp = Get-Date -Format 'yyyyMMdd-HHmmss'
    $script:LogFile = Join-Path $script:LogDir ("uninstall-{0}.log" -f $timestamp)
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

function Save-InstalledPackageMetadata([string]$Id, [string]$Mode, [string]$Location) {
    Ensure-LogInfrastructure
    $entries = @()
    if (Test-Path $script:StateMetaFile) {
        $entries = @(Get-Content -Path $script:StateMetaFile -ErrorAction SilentlyContinue | Where-Object { $_ -and -not $_.StartsWith($Id + '|') })
    }
    $line = ('{0}|{1}|{2}' -f $Id, $Mode, $Location)
    $entries += $line
    Set-Content -Path $script:StateMetaFile -Value $entries
}

function Remove-InstalledPackageMetadata([string]$Id) {
    Ensure-LogInfrastructure
    if (-not (Test-Path $script:StateMetaFile)) { return }
    $entries = @(Get-Content -Path $script:StateMetaFile -ErrorAction SilentlyContinue | Where-Object { $_ -and -not $_.StartsWith($Id + '|') })
    Set-Content -Path $script:StateMetaFile -Value $entries
}

function Get-InstalledPackageMetadata([string]$Id) {
    Ensure-LogInfrastructure
    if (-not (Test-Path $script:StateMetaFile)) { return $null }
    $line = Get-Content -Path $script:StateMetaFile -ErrorAction SilentlyContinue | Where-Object { $_ -and $_.StartsWith($Id + '|') } | Select-Object -First 1
    if (-not $line) { return $null }
    $parts = $line -split '\|', 3
    [pscustomobject]@{ Id = $parts[0]; Mode = $parts[1]; Location = $parts[2] }
}

function Invoke-HiddenProcess([string]$FilePath, [string[]]$Arguments) {
    $process = Start-Process -FilePath $FilePath -ArgumentList $Arguments -WindowStyle Hidden -Wait -PassThru
    return $process.ExitCode
}

function Uninstall-TrackedPackage([string]$Id, [string]$DisplayName) {
    if (-not (Test-InstalledByScriptPackage $Id)) {
        Write-Ok "$DisplayName non risulta installato dallo script"
        return
    }

    $metadata = Get-InstalledPackageMetadata $Id
    $location = if ($metadata) { $metadata.Location } else { '' }
    $mode = if ($metadata) { $metadata.Mode } else { 'default' }

    if ($Id -eq 'Microsoft.PowerShell') {
        if (Test-WingetPackageInstalled $Id) {
            Write-Step "Disinstallo $DisplayName"
            winget uninstall --id $Id --exact --accept-source-agreements --disable-interactivity --silent
            if (-not (Test-WingetPackageInstalled $Id)) {
                Remove-InstalledByScriptPackage $Id
                Remove-InstalledPackageMetadata $Id
                Write-Ok "$DisplayName disinstallato"
            } else {
                Write-WarnMsg "$DisplayName potrebbe richiedere una rimozione manuale o un riavvio"
            }
        }
        return
    }

    if (-not [string]::IsNullOrWhiteSpace($location) -and (Test-Path $location)) {
        if ($mode -eq 'temp') {
            Write-Step "Rimuovo $DisplayName dalla cartella temporanea"
            Remove-Item -Path $location -Recurse -Force -ErrorAction SilentlyContinue
            Remove-InstalledByScriptPackage $Id
            Remove-InstalledPackageMetadata $Id
            Write-Ok "$DisplayName rimosso"
            return
        }

        $uninstallerCandidates = @(
            (Join-Path $location 'unins000.exe'),
            (Join-Path $location 'uninstall.exe'),
            (Join-Path $location 'Uninstall.exe')
        )

        foreach ($candidate in $uninstallerCandidates) {
            if (Test-Path $candidate) {
                Write-Step "Disinstallo $DisplayName"
                $args = @()
                switch ($Id) {
                    'Git.Git' { $args = @('/VERYSILENT', '/SUPPRESSMSGBOXES', '/NORESTART', '/SP-') }
                    'Kitware.CMake' { $args = @('/S') }
                    'MSYS2.MSYS2' { $args = @('/VERYSILENT', '/SUPPRESSMSGBOXES', '/NORESTART', '/SP-') }
                    default { $args = @('/S') }
                }
                Invoke-HiddenProcess $candidate $args | Out-Null
                Start-Sleep -Seconds 2
                if (-not (Test-Path $location)) {
                    Remove-InstalledByScriptPackage $Id
                    Remove-InstalledPackageMetadata $Id
                    Write-Ok "$DisplayName disinstallato"
                    return
                }
            }
        }
    }

    if (-not (Test-WingetPackageInstalled $Id)) {
        Remove-InstalledByScriptPackage $Id
        Remove-InstalledPackageMetadata $Id
        Write-WarnMsg "$DisplayName era segnato come installato dallo script, ma non risulta presente nel sistema"
        return
    }

    Write-Step "Disinstallo $DisplayName"
    winget uninstall --id $Id --exact --accept-source-agreements --disable-interactivity --silent
    if (Test-WingetPackageInstalled $Id) {
        Write-WarnMsg "$DisplayName potrebbe richiedere una rimozione manuale o un riavvio"
    }
    else {
        Remove-InstalledByScriptPackage $Id
        Remove-InstalledPackageMetadata $Id
        Write-Ok "$DisplayName disinstallato"
    }
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
}

function Ensure-Winget {
    if (-not (Get-Command winget -ErrorAction SilentlyContinue)) {
        throw "winget non e disponibile. Installa 'App Installer' dal Microsoft Store e rilancia lo script."
    }
}

function Get-PwshPath {
    Refresh-CommonPaths

    $portableRoot = Join-Path (Split-Path -Parent $PSScriptRoot) 'piboh-portable'
    $portablePreferred = Join-Path $portableRoot 'PowerShell-7\pwsh.exe'
    if (Test-Path $portablePreferred) { return $portablePreferred }
    if (Test-Path $portableRoot) {
        $portablePwsh = Get-ChildItem -Path $portableRoot -Filter 'pwsh.exe' -Recurse -File -ErrorAction SilentlyContinue | Select-Object -First 1
        if ($portablePwsh) { return $portablePwsh.FullName }
    }

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
        '-File', $script:SelfPath
    )

    if (-not [string]::IsNullOrWhiteSpace($RepoDir)) {
        $arguments += @('-RepoDir', $RepoDir)
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
        winget install --id Microsoft.PowerShell --exact --accept-package-agreements --accept-source-agreements --disable-interactivity --silent
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

function Ask-YesNo([string]$Prompt, [bool]$DefaultYes = $false) {
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

function Start-DeferredCleanup([string]$ProjectRoot, [bool]$RemoveBuild, [bool]$RemovePowerShell7) {
    $cmdPath = Join-Path $env:TEMP 'xtetris-cleanup.cmd'
    $lines = @(
        '@echo off',
        'chcp 65001 >nul 2>nul',
        'timeout /t 3 /nobreak >nul'
    )

    if ($RemoveBuild) {
        $buildPath = Join-Path $ProjectRoot 'build'
        $launcherPath = Join-Path $ProjectRoot 'AVVIA GIOCO.bat'
        $lines += ('if exist "{0}" rmdir /s /q "{0}"' -f $buildPath)
        $lines += ('for %%F in ("{0}\*.o" "{0}\*.obj" "{0}\*.exe" "{0}\*.out" "{0}\*.ilk" "{0}\*.pdb") do if exist "%%~F" del /f /q "%%~F"' -f $ProjectRoot)
        $lines += ('if exist "{0}" del /f /q "{0}"' -f $launcherPath)
    }

    if ($RemovePowerShell7) {
        $lines += 'winget uninstall --id Microsoft.PowerShell --exact --accept-source-agreements --disable-interactivity'
    }

    $lines += 'del "%~f0" >nul 2>nul'
    Set-Content -Path $cmdPath -Value ($lines -join "`r`n") -Encoding ASCII

    Start-Process -FilePath 'cmd.exe' -ArgumentList @('/c', $cmdPath) -WindowStyle Minimized | Out-Null
    Write-Ok 'Pulizia finale pianificata'
}

Refresh-CommonPaths
Ensure-PowerShell7Host
Refresh-CommonPaths
Initialize-Log

Write-Host "XTetris Windows Uninstaller $ScriptVersion" -ForegroundColor Magenta

$principal = New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())
$adminRole = [Security.Principal.WindowsBuiltInRole]::Administrator
if (-not $principal.IsInRole($adminRole)) {
    Write-WarnMsg 'Non stai eseguendo lo script come amministratore. In molti casi va bene lo stesso, ma alcuni installer potrebbero chiedere conferma o fallire.'
}

Write-Step 'Verifico winget'
Ensure-Winget
Write-Ok 'winget disponibile'

$repoDirResolved = Resolve-RepoDir $RepoDir
Write-Step "Cartella di lavoro: $repoDirResolved"

Uninstall-TrackedPackage 'Notepad++.Notepad++' 'Notepad++'
Uninstall-TrackedPackage 'Kitware.CMake' 'CMake'
Uninstall-TrackedPackage 'MSYS2.MSYS2' 'MSYS2'

$removeBuild = $false
$buildPath = Join-Path $repoDirResolved 'build'
$rootCompiledFiles = @(Get-ChildItem -Path $repoDirResolved -File -ErrorAction SilentlyContinue | Where-Object {
    $_.Extension -in @('.o', '.obj', '.exe', '.out', '.ilk', '.pdb')
})
if ((Test-Path $buildPath) -or $rootCompiledFiles.Count -gt 0) {
    $removeBuild = Ask-YesNo 'Vuoi eliminare anche la cartella build e gli eventuali file compilati in root di XTetris?'
}
else {
    Write-WarnMsg 'Nessuna build o file compilato trovato: salto la rimozione dei file compilati di XTetris'
}

$removePwsh = (Test-InstalledByScriptPackage 'Microsoft.PowerShell') -and (Test-WingetPackageInstalled 'Microsoft.PowerShell')
if ($removePwsh) {
    Remove-InstalledByScriptPackage 'Microsoft.PowerShell'
    Remove-InstalledPackageMetadata 'Microsoft.PowerShell'
}
if ($removePwsh -or $removeBuild) {
    Write-Step 'Preparo la pulizia finale dopo la chiusura di PowerShell 7'
    Start-DeferredCleanup -ProjectRoot $repoDirResolved -RemoveBuild:$removeBuild -RemovePowerShell7:$removePwsh
    if ($removePwsh) {
        Write-WarnMsg 'PowerShell 7 verra disinstallato subito dopo la chiusura di questa finestra.'
    }
}

Write-Ok 'Disinstallazione completata'
Write-Host 'Puoi chiudere questa finestra.' -ForegroundColor Cyan
Finalize-Log

# Versione script: caricata da version.txt
# File Generato con Arena AI (https://arena.ai/)
