$ScriptDir = $PSScriptRoot
$DebugExe = Join-Path $ScriptDir "build\Debug\SpellPop.exe"
$ReleaseExe = Join-Path $ScriptDir "build\Release\SpellPop.exe"

if (Test-Path $DebugExe) {
    Write-Host "Found Debug build. Launching..." -ForegroundColor Green
    
    # Change to the executable directory so it can find DLLs and assets
    Set-Location (Split-Path $DebugExe)
    
    # Launch the game
    Start-Process ".\SpellPop.exe"
}
elseif (Test-Path $ReleaseExe) {
    Write-Host "Found Release build. Launching..." -ForegroundColor Green
    
    # Change to the executable directory so it can find DLLs and assets
    Set-Location (Split-Path $ReleaseExe)
    
    # Launch the game
    Start-Process ".\SpellPop.exe"
}
else {
    Write-Host "Error: Game executable not found!" -ForegroundColor Red
    Write-Host "Please build the game first."
    Write-Host "Expected location: $DebugExe"
    
    # Pause so the user can see the error if run from Explorer
    Read-Host "Press Enter to exit"
}
