@echo off
setlocal EnableExtensions EnableDelayedExpansion
chcp 65001 >nul 2>nul
set "VERSION_FILE=%~dp0version.txt"
if exist "%VERSION_FILE%" (
  set /p SCRIPT_VERSION=<"%VERSION_FILE%"
) else (
  set "SCRIPT_VERSION=0.0.0-UNKNOWN"
)
set "LOG_DIR=%~dp0log"
if not exist "%LOG_DIR%" mkdir "%LOG_DIR%" >nul 2>nul
set "LOG_FILE=%LOG_DIR%\integrity.log"
>> "%LOG_FILE%" echo [%date% %time%] Avvio verifica integrita repository

set "ROOT=%~dp0.."
set /a ERRORS=0

cls
echo ===============================================
echo      Verifica integrita repository %SCRIPT_VERSION%
echo ===============================================
echo.

call :check_file "%ROOT%\README.md"
call :check_file "%ROOT%\CHANGELOG.md"
call :check_file "%ROOT%\CMakeLists.txt"
call :check_file "%ROOT%\main.c"
call :check_file "%ROOT%\MENU-XTETRIS-WINDOWS.bat"
call :check_dir  "%ROOT%\guide"
call :check_dir  "%ROOT%\piboh-script"
call :check_file "%ROOT%\piboh-script\version.txt"
call :check_dir  "%ROOT%\piboh-portable\Notepad++Portable"
call :check_file "%ROOT%\piboh-portable\Notepad++Portable\shortcuts.xml"
call :check_file "%ROOT%\piboh-portable\Notepad++Portable\plugins\NppMarkdownPanel\NppMarkdownPanel.dll"
call :check_dir  "%ROOT%\Elements"
call :check_dir  "%ROOT%\GameSetting"
call :check_dir  "%ROOT%\PianoDiGioco"
call :check_dir  "%ROOT%\Tetramino"

echo.
if "%ERRORS%"=="0" (
  echo [OK] Nessun problema rilevato.
  >> "%LOG_FILE%" echo [%date% %time%] Verifica completata senza errori
) else (
  echo [WARN] Trovati %ERRORS% problemi di integrita.
  >> "%LOG_FILE%" echo [%date% %time%] Verifica completata con %ERRORS% errori
)

echo.
pause
exit /b 0

:check_file
if exist "%~1" (
  echo [OK] File presente: %~1
) else (
  echo [ERRORE] File mancante: %~1
  set /a ERRORS+=1
)
goto :eof

:check_dir
if exist "%~1" (
  echo [OK] Cartella presente: %~1
) else (
  echo [ERRORE] Cartella mancante: %~1
  set /a ERRORS+=1
)
goto :eof

REM Versione script: caricata da version.txt
REM File Generato con Arena AI (https://arena.ai/)
