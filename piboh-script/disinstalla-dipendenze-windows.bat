@echo off
setlocal EnableExtensions
chcp 65001 >nul 2>nul
set "SCRIPT_VERSION=1.0.21-STABLE"
set "LOG_DIR=%~dp0log"
if not exist "%LOG_DIR%" mkdir "%LOG_DIR%" >nul 2>nul
set "STATE_FILE=%LOG_DIR%\installed-packages.txt"
if not exist "%STATE_FILE%" type nul > "%STATE_FILE%"
set "LOG_FILE=%LOG_DIR%\uninstall-launcher.log"
>> "%LOG_FILE%" echo [%date% %time%] Avvio piboh-script/disinstalla-dipendenze-windows.bat

echo XTetris Windows Uninstaller %SCRIPT_VERSION%

echo.
set "SCRIPT_PS1=%~dp0disinstalla-dipendenze-windows.ps1"
if not exist "%SCRIPT_PS1%" set "SCRIPT_PS1=%~dp0scripts\disinstalla-dipendenze-windows.ps1"

if not exist "%SCRIPT_PS1%" (
 echo.
 echo ERRORE: impossibile trovare lo script PowerShell di disinstallazione.
 echo Percorso cercato: "%~dp0disinstalla-dipendenze-windows.ps1"
 echo Percorso alternativo: "%~dp0scripts\disinstalla-dipendenze-windows.ps1"
 >> "%LOG_FILE%" echo [%date% %time%] Errore durante esecuzione
pause
 exit /b 1
)

call :find_pwsh
if defined PWSH goto run_pwsh

echo ==> PowerShell 7 non trovato. Provo a installarlo con winget...
where winget >nul 2>nul
if errorlevel 1 (
 echo ERRORE: winget non disponibile. Installa App Installer dal Microsoft Store.
 >> "%LOG_FILE%" echo [%date% %time%] Errore durante esecuzione
pause
 exit /b 1
)

winget install --id Microsoft.PowerShell --exact --accept-package-agreements --accept-source-agreements --disable-interactivity
if errorlevel 1 (
 echo ERRORE: installazione automatica di PowerShell 7 fallita.
 >> "%LOG_FILE%" echo [%date% %time%] Errore durante esecuzione
pause
 exit /b 1
)

findstr /x /c:"Microsoft.PowerShell" "%STATE_FILE%" >nul 2>nul
if errorlevel 1 echo Microsoft.PowerShell>> "%STATE_FILE%"

call :find_pwsh
if not defined PWSH (
 echo ERRORE: PowerShell 7 risulta installato ma pwsh.exe non e stato trovato.
 >> "%LOG_FILE%" echo [%date% %time%] Errore durante esecuzione
pause
 exit /b 1
)

:run_pwsh
"%PWSH%" -NoProfile -ExecutionPolicy Bypass -File "%SCRIPT_PS1%" %*
if errorlevel 1 (
 echo.
 echo Lo script PowerShell ha restituito un errore.
 >> "%LOG_FILE%" echo [%date% %time%] Errore durante esecuzione
pause
 exit /b 1
)

echo.
echo Operazione completata.
>> "%LOG_FILE%" echo [%date% %time%] Fine con successo
pause
exit /b 0

:find_pwsh
set "PWSH="
where pwsh >nul 2>nul
if not errorlevel 1 (
 set "PWSH=pwsh"
 goto :eof
)
if exist "%ProgramFiles%\PowerShell\7\pwsh.exe" (
 set "PWSH=%ProgramFiles%\PowerShell\7\pwsh.exe"
 goto :eof
)
if exist "%ProgramFiles%\PowerShell\7-preview\pwsh.exe" (
 set "PWSH=%ProgramFiles%\PowerShell\7-preview\pwsh.exe"
 goto :eof
)
if exist "%LOCALAPPDATA%\Microsoft\WindowsApps\pwsh.exe" (
 set "PWSH=%LOCALAPPDATA%\Microsoft\WindowsApps\pwsh.exe"
 goto :eof
)
goto :eof

REM Versione script: 1.0.21-STABLE
REM File Generato con Arena AI (https://arena.ai/)
