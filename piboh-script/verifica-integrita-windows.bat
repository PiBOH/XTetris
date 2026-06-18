@echo off
setlocal EnableExtensions EnableDelayedExpansion
chcp 65001 >nul 2>nul
set "VERSION_FILE=%~dp0version.txt"
if exist "%VERSION_FILE%" (
  set /p SCRIPT_VERSION=<"%VERSION_FILE%"
) else (
  set "SCRIPT_VERSION=0.0.0-UNKNOWN"
)
for /F %%e in ('echo prompt $E^| cmd') do set "ESC=%%e"
set "LOG_DIR=%~dp0log"
if not exist "%LOG_DIR%" mkdir "%LOG_DIR%" >nul 2>nul
set "LOG_FILE=%LOG_DIR%\integrity.log"
>> "%LOG_FILE%" echo [%date% %time%] Avvio verifica integrita repository

set "ROOT=%~dp0.."
set /a ERRORS=0
set /a WARNS=0

cls
echo ===============================================
echo      Verifica integrita repository %SCRIPT_VERSION%
echo ===============================================
echo.

call :check_critical_file "%ROOT%\README.md"
call :check_critical_file "%ROOT%\CHANGELOG.md"
call :check_critical_file "%ROOT%\CMakeLists.txt"
call :check_critical_file "%ROOT%\main.c"
call :check_critical_file "%ROOT%\MENU-XTETRIS-WINDOWS.bat"
call :check_critical_dir  "%ROOT%\piboh-script"
call :check_critical_file "%ROOT%\piboh-script\pulisci-log-cache-windows.bat"
call :check_critical_file "%ROOT%\piboh-script\version.txt"
call :check_critical_dir  "%ROOT%\piboh-portable\Notepad++Portable"
call :check_critical_dir  "%ROOT%\piboh-portable\PowerShell-7"
call :check_critical_file "%ROOT%\piboh-portable\PowerShell-7\pwsh.exe"
call :check_critical_file "%ROOT%\piboh-portable\Notepad++Portable\shortcuts.xml"
call :check_critical_file "%ROOT%\piboh-portable\Notepad++Portable\plugins\NppMarkdownPanel\NppMarkdownPanel.dll"
call :check_critical_dir  "%ROOT%\Elements"
call :check_critical_dir  "%ROOT%\GameSetting"
call :check_critical_dir  "%ROOT%\PianoDiGioco"
call :check_critical_dir  "%ROOT%\Tetramino"

call :check_optional_dir  "%ROOT%\guide"
call :check_optional_file "%ROOT%\AVVIA GIOCO.bat"
call :check_optional_dir  "%ROOT%\build"

echo.
if "%ERRORS%"=="0" if "%WARNS%"=="0" (
  call :print_ok "Verifica completata senza problemi."
  >> "%LOG_FILE%" echo [%date% %time%] Verifica completata senza errori o warning
) else if "%ERRORS%"=="0" (
  call :print_warn "Verifica completata con %WARNS% warning opzionali."
  >> "%LOG_FILE%" echo [%date% %time%] Verifica completata con %WARNS% warning
) else (
  call :print_err "Verifica completata con %ERRORS% errori critici e %WARNS% warning."
  >> "%LOG_FILE%" echo [%date% %time%] Verifica completata con %ERRORS% errori e %WARNS% warning
)

echo.
pause
exit /b 0

:print_ok
echo %ESC%[92m[OK] %~1%ESC%[0m
goto :eof

:print_warn
echo %ESC%[93m[WARN] %~1%ESC%[0m
goto :eof

:print_err
echo %ESC%[91m[ERRORE] %~1%ESC%[0m
goto :eof

:check_critical_file
if exist "%~1" (
  call :print_ok "File critico presente: %~1"
) else (
  call :print_err "File critico mancante: %~1"
  set /a ERRORS+=1
)
goto :eof

:check_critical_dir
if exist "%~1" (
  call :print_ok "Cartella critica presente: %~1"
) else (
  call :print_err "Cartella critica mancante: %~1"
  set /a ERRORS+=1
)
goto :eof

:check_optional_file
if exist "%~1" (
  call :print_ok "File opzionale presente: %~1"
) else (
  call :print_warn "File opzionale mancante: %~1"
  set /a WARNS+=1
)
goto :eof

:check_optional_dir
if exist "%~1" (
  call :print_ok "Cartella opzionale presente: %~1"
) else (
  call :print_warn "Cartella opzionale mancante: %~1"
  set /a WARNS+=1
)
goto :eof

REM Versione script: caricata da version.txt
REM File Generato con Arena AI (https://arena.ai/)
