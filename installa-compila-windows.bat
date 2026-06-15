@echo off
setlocal
set SCRIPT=%~dp0scripts\installa-compila-windows.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File "%SCRIPT%" %*
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
