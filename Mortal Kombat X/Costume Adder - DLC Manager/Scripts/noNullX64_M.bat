@echo off & setlocal EnableDelayedExpansion
del noNull.txt >Nul
cls
echo.Loading File 1...
start /wait Scripts\NoNullX64.exe
del X64_Dec.txt >nul
copy noNull.txt X64_Dec.txt >nul
del noNull.txt >nul
cls

