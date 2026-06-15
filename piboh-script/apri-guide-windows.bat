@echo off
setlocal EnableExtensions EnableDelayedExpansion
chcp 65001 >nul 2>nul
set "SCRIPT_VERSION=1.0.23.2"
set "LOG_DIR=%~dp0log"
if not exist "%LOG_DIR%" mkdir "%LOG_DIR%" >nul 2>nul
set "LOG_FILE=%LOG_DIR%\guide-menu.log"
>> "%LOG_FILE%" echo [%date% %time%] Avvio piboh-script/apri-guide-windows.bat

:guides_menu
cls
echo ===============================================
echo           Guide XTetris Windows %SCRIPT_VERSION%
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

if "%GUIDE_CHOICE%"=="1" call :open_guide "%~dp0..\README.md"
if "%GUIDE_CHOICE%"=="2" call :open_guide "%~dp0..\guide\GUIDA-WINDOWS.md"
if "%GUIDE_CHOICE%"=="3" call :open_guide "%~dp0..\guide\GUIDA-WINDOWS-RAPIDA.md"
if "%GUIDE_CHOICE%"=="4" call :open_guide "%~dp0..\guide\GUIDA-MSYS2.md"
if "%GUIDE_CHOICE%"=="5" call :open_guide "%~dp0..\guide\GUIDA-CLION-WINDOWS.md"
if "%GUIDE_CHOICE%"=="6" call :open_guide "%~dp0..\guide\GUIDA-VSCODE-WINDOWS.md"
if "%GUIDE_CHOICE%"=="7" call :open_guide "%~dp0..\guide\GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md"
if "%GUIDE_CHOICE%"=="8" goto end

goto guides_menu

:open_guide
set "GUIDE_FILE=%~1"
call :find_notepadpp
if not defined NPP_EXE (
  echo.
  echo ERRORE: Notepad++ non trovato.
  echo Verifica che la copia portable esista in piboh-portable\Notepad++Portable\
  >> "%LOG_FILE%" echo [%date% %time%] ERRORE: Notepad++ non trovato
  pause
  goto :eof
)

if not exist "%GUIDE_FILE%" (
  echo.
  echo ERRORE: guida non trovata: "%GUIDE_FILE%"
  >> "%LOG_FILE%" echo [%date% %time%] ERRORE: guida non trovata: %GUIDE_FILE%
  pause
  goto :eof
)

>> "%LOG_FILE%" echo [%date% %time%] Apertura guida: %GUIDE_FILE%
start "Notepad++" "%NPP_EXE%" "%GUIDE_FILE%"
goto :eof

:find_notepadpp
set "NPP_EXE="
if exist "%~dp0..\piboh-portable\Notepad++Portable\notepad++.exe" (
  set "NPP_EXE=%~dp0..\piboh-portable\Notepad++Portable\notepad++.exe"
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

:end
>> "%LOG_FILE%" echo [%date% %time%] Chiusura menu guide
exit /b 0

REM Versione script: 1.0.23.2
REM File Generato con Arena AI (https://arena.ai/)
