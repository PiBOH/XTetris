@echo off
setlocal EnableExtensions EnableDelayedExpansion
chcp 65001 >nul 2>nul
set "VERSION_FILE=%~dp0version.txt"
if exist "%VERSION_FILE%" (
  set /p SCRIPT_VERSION=<"%VERSION_FILE%"
) else (
  set "SCRIPT_VERSION=0.0.0-UNKNOWN"
)
for %%I in ("%~dp0..") do set "ROOT=%%~fI"
set "LOG_DIR=%~dp0log"
set "TEMP_DIR=%ROOT%\piboh-temp"
set /a REMOVED_LOG_FILES=0
set /a REMOVED_CACHE_FILES=0

cls
echo XTetris Windows Cleanup %SCRIPT_VERSION%
echo.
echo Questo comando rimuove:
echo - tutti i file dentro piboh-script\log\
echo - la cartella piboh-temp\
echo - ogni altro file del repository con "cache" nel nome
set /p CONFIRM=Procedere con la pulizia? [s/N]: 
if /I not "%CONFIRM%"=="S" if /I not "%CONFIRM%"=="SI" if /I not "%CONFIRM%"=="Y" if /I not "%CONFIRM%"=="YES" (
  echo.
  echo Operazione annullata.
  pause
  exit /b 0
)

echo.
if exist "%LOG_DIR%" (
  for /r "%LOG_DIR%" %%F in (*) do (
    if exist "%%~fF" (
      del /f /q "%%~fF" >nul 2>nul
      if not exist "%%~fF" set /a REMOVED_LOG_FILES+=1
    )
  )
  for /f "delims=" %%D in ('dir "%LOG_DIR%" /ad /b /s 2^>nul ^| sort /r') do rd "%%D" >nul 2>nul
)

if exist "%TEMP_DIR%" (
  rmdir /s /q "%TEMP_DIR%" >nul 2>nul
)

for /r "%ROOT%" %%F in (*cache*) do (
  if /I not "%%~fF"=="%~f0" (
    del /f /q "%%~fF" >nul 2>nul
    if not exist "%%~fF" set /a REMOVED_CACHE_FILES+=1
  )
)

echo [OK] File rimossi da piboh-script\log: !REMOVED_LOG_FILES!
if exist "%TEMP_DIR%" (
  echo [WARN] La cartella piboh-temp non e stata rimossa completamente: "%TEMP_DIR%"
) else (
  echo [OK] Cartella piboh-temp pulita
)
echo [OK] Altri file con "cache" nel nome rimossi: !REMOVED_CACHE_FILES!
echo [OK] Pulizia log e cache completata

echo.
pause
exit /b 0

REM Versione script: caricata da version.txt
REM File Generato con Arena AI (https://arena.ai/)
