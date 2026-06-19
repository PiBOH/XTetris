@echo off
setlocal EnableExtensions EnableDelayedExpansion
chcp 65001 >nul 2>nul
set "VERSION_FILE=%~dp0piboh-script\version.txt"
if exist "%VERSION_FILE%" (
  set /p SCRIPT_VERSION=<"%VERSION_FILE%"
) else (
  set "SCRIPT_VERSION=0.0.0-UNKNOWN"
)
set "LOG_DIR=%~dp0piboh-script\log"
if not exist "%LOG_DIR%" mkdir "%LOG_DIR%" >nul 2>nul
set "LOG_FILE=%LOG_DIR%\menu.log"
>> "%LOG_FILE%" echo [%date% %time%] Avvio MENU-XTETRIS-WINDOWS.bat

:menu
call :flush_input
cls
echo ===============================================
echo      Pre-XTetris Windows Menu %SCRIPT_VERSION%
echo ===============================================
echo.
echo  1. Installa prerequisiti e compila XTetris
echo  2. Compila e avvia subito XTetris
echo  3. Avvia il gioco gia compilato
echo  4. Disinstalla dipendenze / rimuovi build e file compilati di XTetris
echo  5. Apri una guida in Notepad++
echo  6. Visualizza CHANGELOG.md
echo  7. Controlla integrita del repository
echo  8. Pulisci log e cache
echo  9. Esci
echo.
set "CHOICE="
set /p CHOICE=Seleziona un'opzione [1-9]: 
>> "%LOG_FILE%" echo [%date% %time%] Scelta menu principale: %CHOICE%

if "%CHOICE%"=="1" goto install_build
if "%CHOICE%"=="2" goto build_and_run
if "%CHOICE%"=="3" goto run_game
if "%CHOICE%"=="4" goto uninstall_all
if "%CHOICE%"=="5" goto guides_launcher
if "%CHOICE%"=="6" goto changelog_launcher
if "%CHOICE%"=="7" goto integrity_check
if "%CHOICE%"=="8" goto cleanup_logs_cache
if "%CHOICE%"=="9" goto end

echo.
echo Opzione non valida. Inserisci un numero da 1 a 9.
pause
goto menu

:install_build
if exist "%~dp0piboh-script\installa-compila-windows.bat" (
  call "%~dp0piboh-script\installa-compila-windows.bat"
  call :flush_input
) else (
  echo.
  echo ERRORE: file non trovato: piboh-script\installa-compila-windows.bat
  pause
)
goto menu

:build_and_run
if exist "%~dp0piboh-script\installa-compila-windows.bat" (
  start "XTetris Build and Run" /wait "%ComSpec%" /c ""%~dp0piboh-script\installa-compila-windows.bat" -RunAfterBuild"
  call :flush_input
) else (
  echo.
  echo ERRORE: file non trovato: piboh-script\installa-compila-windows.bat
  pause
)
goto menu

:run_game
if exist "%~dp0AVVIA GIOCO.bat" (
  start "XTetris Run" /wait "%ComSpec%" /c ""%~dp0AVVIA GIOCO.bat""
  call :flush_input
) else if exist "%~dp0piboh-script\installa-compila-windows.bat" (
  echo.
  echo AVVIA GIOCO.bat non trovato, genero la build e avvio il gioco...
  start "XTetris Build and Run" /wait "%ComSpec%" /c ""%~dp0piboh-script\installa-compila-windows.bat" -RunAfterBuild"
  call :flush_input
) else (
  echo.
  echo ERRORE: nessun launcher disponibile.
  pause
)
goto menu

:uninstall_all
if exist "%~dp0piboh-script\disinstalla-dipendenze-windows.bat" (
  call "%~dp0piboh-script\disinstalla-dipendenze-windows.bat"
  call :flush_input
) else (
  echo.
  echo ERRORE: file non trovato: piboh-script\disinstalla-dipendenze-windows.bat
  pause
)
goto menu

:guides_launcher
if exist "%~dp0piboh-script\apri-guide-windows.bat" (
  call "%~dp0piboh-script\apri-guide-windows.bat"
  call :flush_input
) else (
  echo.
  echo ERRORE: file non trovato: piboh-script\apri-guide-windows.bat
  pause
)
goto menu

:changelog_launcher
if exist "%~dp0piboh-script\apri-guide-windows.bat" (
  call "%~dp0piboh-script\apri-guide-windows.bat" "%~dp0CHANGELOG.md"
  call :flush_input
) else (
  echo.
  echo ERRORE: file non trovato: piboh-script\apri-guide-windows.bat
  pause
)
goto menu

:integrity_check
if exist "%~dp0piboh-script\verifica-integrita-windows.bat" (
  call "%~dp0piboh-script\verifica-integrita-windows.bat"
  call :flush_input
) else (
  echo.
  echo ERRORE: file non trovato: piboh-script\verifica-integrita-windows.bat
  pause
)
goto menu

:cleanup_logs_cache
if exist "%~dp0piboh-script\pulisci-log-cache-windows.bat" (
  call "%~dp0piboh-script\pulisci-log-cache-windows.bat"
  call :flush_input
) else (
  echo.
  echo ERRORE: file non trovato: piboh-script\pulisci-log-cache-windows.bat
  pause
)
goto menu

:flush_input
set "FLUSH_HOST="
if exist "%~dp0piboh-portable\PowerShell-7\pwsh.exe" (
  set "FLUSH_HOST=%~dp0piboh-portable\PowerShell-7\pwsh.exe"
) else if exist "%~dp0piboh-portable\PowerShell-7.7.0-preview.2-win-x64\pwsh.exe" (
  set "FLUSH_HOST=%~dp0piboh-portable\PowerShell-7.7.0-preview.2-win-x64\pwsh.exe"
) else where pwsh >nul 2>nul
if not errorlevel 1 (
  set "FLUSH_HOST=pwsh"
) else if exist "%ProgramFiles%\PowerShell\7\pwsh.exe" (
  set "FLUSH_HOST=%ProgramFiles%\PowerShell\7\pwsh.exe"
) else if exist "%ProgramFiles%\PowerShell\7-preview\pwsh.exe" (
  set "FLUSH_HOST=%ProgramFiles%\PowerShell\7-preview\pwsh.exe"
) else (
  set "FLUSH_HOST=powershell"
)
"%FLUSH_HOST%" -NoProfile -Command "try { $Host.UI.RawUI.FlushInputBuffer() } catch { }" >nul 2>nul
goto :eof

:end
echo.
echo Chiusura menu XTetris.
exit /b 0

REM Versione script: caricata da piboh-script\version.txt
REM File Generato con Arena AI (https://arena.ai/)
