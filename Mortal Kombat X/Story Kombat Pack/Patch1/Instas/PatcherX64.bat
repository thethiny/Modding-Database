@echo off
title X64TOC Patcher
del X64_Dec.txt 2>nul
copy X64TOC.txt X64_Dec.txt >nul
copy X64TOC.txt X64TOC_BackupSKP.txt
Instas\AES_X64.exe -d X64_Dec.txt
start /wait Instas\NoNullX64.exe
copy noNull.txt X64_Dec.txt >nul
del noNull.txt 2>nul

echo.0 0 0 0 11 ..\Asset\Rain_Victory.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\Rain_Victory_MapAssets.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\Sindel_Victory.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\Sindel_Victory_MapAssets.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\Baraka_Victory.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\Baraka_Victory_MapAssets.xxx 11>>X64_Dec.txt
echo. >>X64_Dec.txt

copy X64_Dec.txt X64TOC.txt
del /Q X64_Dec.txt 2>nul
start /wait Instas\AES_X64.exe -e X64TOC.txt

cls

