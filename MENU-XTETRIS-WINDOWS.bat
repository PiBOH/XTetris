@echo off
setlocal EnableExtensions EnableDelayedExpansion
chcp 65001 >nul 2>nul
set "SCRIPT_VERSION=1.0.23.2"
set "LOG_DIR=%~dp0piboh-script\log"
if not exist "%LOG_DIR%" mkdir "%LOG_DIR%" >nul 2>nul
set "LOG_FILE=%LOG_DIR%\menu.log"
>> "%LOG_FILE%" echo [%date% %time%] Avvio MENU-XTETRIS-WINDOWS.bat

:menu
call :flush_input
cls
echo ===============================================
echo         XTetris Windows Menu %SCRIPT_VERSION%
echo ===============================================
echo.
echo  1. Installa prerequisiti e compila XTetris
echo  2. Compila e avvia subito XTetris
echo  3. Avvia il gioco gia compilato
echo  4. Disinstalla dipendenze / rimuovi build e file compilati di XTetris
echo  5. Apri una guida in Notepad++
echo  6. Esci
echo.
choice /c 123456 /n /m "Seleziona un'opzione [1-6]: "
set "CHOICE=%ERRORLEVEL%"
>> "%LOG_FILE%" echo [%date% %time%] Scelta menu principale: %CHOICE%

if "%CHOICE%"=="1" goto install_build
if "%CHOICE%"=="2" goto build_and_run
if "%CHOICE%"=="3" goto run_game
if "%CHOICE%"=="4" goto uninstall_all
if "%CHOICE%"=="5" goto guides_menu
if "%CHOICE%"=="6" goto end

echo.
echo Opzione non valida.
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
if exist "%~dp0AVVIA-XTETRIS-WINDOWS.bat" (
  start "XTetris Quick Start" /wait "%ComSpec%" /c ""%~dp0AVVIA-XTETRIS-WINDOWS.bat""
  call :flush_input
) else if exist "%~dp0piboh-script\installa-compila-windows.bat" (
  echo.
  echo AVVIA-XTETRIS-WINDOWS.bat non trovato, uso il fallback automatico...
  start "XTetris Build and Run" /wait "%ComSpec%" /c ""%~dp0piboh-script\installa-compila-windows.bat" -RunAfterBuild"
  call :flush_input
) else (
  echo.
  echo ERRORE: file non trovato: AVVIA-XTETRIS-WINDOWS.bat
  echo ERRORE: file non trovato: piboh-script\installa-compila-windows.bat
  pause
)
goto menu

:run_game
if exist "%~dp0AVVIA GIOCO.bat" (
  start "XTetris Run" /wait "%ComSpec%" /c ""%~dp0AVVIA GIOCO.bat""
  call :flush_input
) else (
  echo.
  echo AVVIA GIOCO.bat non trovato.
  echo Provo con AVVIA-XTETRIS-WINDOWS.bat...
  if exist "%~dp0AVVIA-XTETRIS-WINDOWS.bat" (
    start "XTetris Quick Start" /wait "%ComSpec%" /c ""%~dp0AVVIA-XTETRIS-WINDOWS.bat""
    call :flush_input
  ) else if exist "%~dp0piboh-script\installa-compila-windows.bat" (
    echo Uso il fallback automatico tramite piboh-script\installa-compila-windows.bat -RunAfterBuild
    start "XTetris Build and Run" /wait "%ComSpec%" /c ""%~dp0piboh-script\installa-compila-windows.bat" -RunAfterBuild"
    call :flush_input
  ) else (
    echo.
    echo ERRORE: nessun launcher disponibile.
    pause
  )
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

:guides_menu
call :flush_input
cls
echo ===============================================
echo              Guide XTetris Windows
echo ===============================================
echo.
echo  1. README.md
echo  2. GUIDA-WINDOWS.md
echo  3. GUIDA-WINDOWS-RAPIDA.md
echo  4. GUIDA-MSYS2.md
echo  5. GUIDA-CLION-WINDOWS.md
echo  6. GUIDA-VSCODE-WINDOWS.md
echo  7. GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md
echo  8. Torna al menu principale
echo.
choice /c 12345678 /n /m "Seleziona una guida [1-8]: "
set "GUIDE_CHOICE=%ERRORLEVEL%"
>> "%LOG_FILE%" echo [%date% %time%] Scelta menu guide: %GUIDE_CHOICE%

if "%GUIDE_CHOICE%"=="1" call :open_guide "%~dp0README.md"
if "%GUIDE_CHOICE%"=="2" call :open_guide "%~dp0guide\GUIDA-WINDOWS.md"
if "%GUIDE_CHOICE%"=="3" call :open_guide "%~dp0guide\GUIDA-WINDOWS-RAPIDA.md"
if "%GUIDE_CHOICE%"=="4" call :open_guide "%~dp0guide\GUIDA-MSYS2.md"
if "%GUIDE_CHOICE%"=="5" call :open_guide "%~dp0guide\GUIDA-CLION-WINDOWS.md"
if "%GUIDE_CHOICE%"=="6" call :open_guide "%~dp0guide\GUIDA-VSCODE-WINDOWS.md"
if "%GUIDE_CHOICE%"=="7" call :open_guide "%~dp0guide\GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md"
if "%GUIDE_CHOICE%"=="8" goto menu

goto guides_menu

:open_guide
set "GUIDE_FILE=%~1"
call :find_notepadpp
if not defined NPP_EXE (
  echo.
  echo ERRORE: Notepad++ non trovato.
  echo Installa prima i prerequisiti con piboh-script\installa-compila-windows.bat.
  pause
  goto :eof
)

if not exist "%GUIDE_FILE%" (
  echo.
  echo ERRORE: guida non trovata: "%GUIDE_FILE%"
  pause
  goto :eof
)

>> "%LOG_FILE%" echo [%date% %time%] Apertura guida: %GUIDE_FILE%
start "Notepad++" "%NPP_EXE%" "%GUIDE_FILE%"
goto :eof

:find_notepadpp
set "NPP_EXE="
if exist "%~dp0piboh-portable\Notepad++Portable\notepad++.exe" (
  set "NPP_EXE=%~dp0piboh-portable\Notepad++Portable\notepad++.exe"
  goto :eof
)
where notepad++ >nul 2>nul
if not errorlevel 1 (
  for /f "delims=" %%I in ('where notepad++') do (
    set "NPP_EXE=%%I"
    goto :eof
  )
)
if exist "%ProgramFiles%\Notepad++\notepad++.exe" (
  set "NPP_EXE=%ProgramFiles%\Notepad++\notepad++.exe"
  goto :eof
)
if exist "%ProgramFiles(x86)%\Notepad++\notepad++.exe" (
  set "NPP_EXE=%ProgramFiles(x86)%\Notepad++\notepad++.exe"
  goto :eof
)
if exist "%LOCALAPPDATA%\Programs\Notepad++\notepad++.exe" (
  set "NPP_EXE=%LOCALAPPDATA%\Programs\Notepad++\notepad++.exe"
  goto :eof
)
goto :eof

:flush_input
set "FLUSH_HOST="
where pwsh >nul 2>nul
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

REM Versione script: 1.0.23.2
REM File Generato con Arena AI (https://arena.ai/)
