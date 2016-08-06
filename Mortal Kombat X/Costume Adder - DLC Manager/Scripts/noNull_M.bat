@echo off & setlocal EnableDelayedExpansion
del noNull.txt >Nul
cls
echo.Loading File 2...
start /wait Scripts\noNull.exe
copy noNull.txt Extract\$StartupCacheDir$\Config\X64-MK10Game.ini >nul
del NoNull.txt >nul
cls
echo Done Modifying!

