@echo off
setlocal
chcp 65001 >nul 2>nul

set "SCRIPT_PS1=%~dp0installa-compila-windows.ps1"
if not exist "%SCRIPT_PS1%" set "SCRIPT_PS1=%~dp0scripts\installa-compila-windows.ps1"

if not exist "%SCRIPT_PS1%" (
  echo.
  echo ERRORE: impossibile trovare lo script PowerShell automatico.
  echo Percorso cercato: "%~dp0installa-compila-windows.ps1"
  echo Percorso alternativo: "%~dp0scripts\installa-compila-windows.ps1"
  pause
  exit /b 1
)

powershell -NoProfile -ExecutionPolicy Bypass -File "%SCRIPT_PS1%" %*
if errorlevel 1 (
  echo.
  echo Lo script PowerShell ha restituito un errore.
  pause
  exit /b 1
)

echo.
echo Operazione completata.
pause
REM File Generato con Arena AI (https://arena.ai/)
