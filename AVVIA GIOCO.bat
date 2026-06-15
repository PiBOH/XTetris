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
REM Versione launcher generato: 1.0.9k-STABLE
REM File Generato con Arena AI (https://arena.ai/)
