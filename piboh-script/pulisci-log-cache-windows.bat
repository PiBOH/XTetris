@echo off
setlocal EnableExtensions EnableDelayedExpansion
chcp 65001 >nul 2>nul
set "VERSION_FILE=%~dp0version.txt"
if exist "%VERSION_FILE%" (
  set /p SCRIPT_VERSION=<"%VERSION_FILE%"
) else (
  set "SCRIPT_VERSION=0.0.0-UNKNOWN"
)
set "ROOT=%~dp0.."
set "LOG_DIR=%~dp0log"
set "TEMP_DIR=%ROOT%\piboh-temp"
set "LOG_FILE=%LOG_DIR%\cleanup.log"
if not exist "%LOG_DIR%" mkdir "%LOG_DIR%" >nul 2>nul
>> "%LOG_FILE%" echo [%date% %time%] Avvio pulisci-log-cache-windows.bat

echo XTetris Windows Cleanup %SCRIPT_VERSION%
echo.

echo Questo comando rimuove:
echo - i file .log in piboh-script\log\
echo - la cartella piboh-temp\
echo.
set /p CONFIRM=Procedere con la pulizia? [s/N]: 
if /I not "%CONFIRM%"=="S" if /I not "%CONFIRM%"=="SI" if /I not "%CONFIRM%"=="Y" if /I not "%CONFIRM%"=="YES" (
  echo.
  echo Operazione annullata.
  >> "%LOG_FILE%" echo [%date% %time%] Pulizia annullata dall'utente
  pause
  exit /b 0
)

echo.
set /a REMOVED_LOGS=0
if exist "%LOG_DIR%" (
  for %%F in ("%LOG_DIR%\*.log") do (
    if exist "%%~fF" (
      if /I not "%%~nxF"=="cleanup.log" (
        del /f /q "%%~fF" >nul 2>nul
        set /a REMOVED_LOGS+=1
      )
    )
  )
)

if exist "%TEMP_DIR%" (
  rmdir /s /q "%TEMP_DIR%" >nul 2>nul
)

echo [OK] File di log rimossi: !REMOVED_LOGS!
if exist "%TEMP_DIR%" (
  echo [WARN] La cartella piboh-temp non e stata rimossa completamente: "%TEMP_DIR%"
  >> "%LOG_FILE%" echo [%date% %time%] WARN: piboh-temp non rimossa completamente
) else (
  echo [OK] Cartella piboh-temp pulita
)

echo [OK] Pulizia log e cache completata
>> "%LOG_FILE%" echo [%date% %time%] Pulizia completata

echo.
pause
exit /b 0

REM Versione script: caricata da version.txt
REM File Generato con Arena AI (https://arena.ai/)
