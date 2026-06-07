@echo off
setlocal

set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "VCVARS="

if exist "%VSWHERE%" (
    for /f "usebackq delims=" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
        set "VSINSTALL=%%i"
    )
)

if defined VSINSTALL (
    set "VCVARS=%VSINSTALL%\VC\Auxiliary\Build\vcvars64.bat"
)

if exist "%VCVARS%" (
    call "%VCVARS%" >nul
    cl /nologo /EHsc /std:c++17 /W4 /O2 main.cpp matrix.cpp /Fe:task1.exe
    if errorlevel 1 exit /b 1
    echo.
    echo Сборка успешна: task1.exe
    exit /b 0
)

where g++ >nul 2>&1
if %errorlevel%==0 (
    g++ -std=c++17 -Wall -Wextra -O2 -o task1.exe main.cpp matrix.cpp
    if errorlevel 1 exit /b 1
    echo.
    echo Сборка успешна: task1.exe
    exit /b 0
)

echo Не найден компилятор C++. Установите Visual Studio с C++ или MinGW.
exit /b 1
