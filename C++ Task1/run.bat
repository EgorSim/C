@echo off
setlocal
cd /d "%~dp0"

if not exist task1.exe (
    call build.bat
    if errorlevel 1 (
        pause
        exit /b 1
    )
)

task1.exe
echo.
pause
