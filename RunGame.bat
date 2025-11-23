@echo off
setlocal

REM Get the directory of this script
set "SCRIPT_DIR=%~dp0"
cd /d "%SCRIPT_DIR%"

REM Define paths
set "DEBUG_EXE=build\Debug\SpellPop.exe"
set "RELEASE_EXE=build\Release\SpellPop.exe"

REM Check for Debug build
if exist "%DEBUG_EXE%" (
    echo Found Debug build.
    echo Launching SpellPop...
    
    REM Change to the executable directory so it can find DLLs and assets
    cd build\Debug
    
    REM Launch the game
    start "" "SpellPop.exe"
    exit /b 0
)

REM Check for Release build
if exist "%RELEASE_EXE%" (
    echo Found Release build.
    echo Launching SpellPop...
    
    REM Change to the executable directory so it can find DLLs and assets
    cd build\Release
    
    REM Launch the game
    start "" "SpellPop.exe"
    exit /b 0
)

echo.
echo Error: Game executable not found!
echo.
echo Please build the game first.
echo Expected location: %DEBUG_EXE%
echo.
pause
exit /b 1
