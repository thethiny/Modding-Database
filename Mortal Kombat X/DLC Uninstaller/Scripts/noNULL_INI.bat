@echo off & setlocal EnableDelayedExpansion
del noNull.txt 2>Nul
cls
echo.Loading COALSCED.INI...
start /wait Scripts\noNull.exe
copy noNull.txt Extract\$StartupCacheDir$\Config\X64-MK10Game.ini >nul
del NoNull.txt 2>nul
cls
echo Done Modifying!

