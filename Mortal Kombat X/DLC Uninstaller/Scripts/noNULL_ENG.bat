@echo off & setlocal EnableDelayedExpansion
del noNull.txt 2>Nul
cls
echo.Loading COALSCED.ENG...
Scripts\iconv -f UNICODELITTLE -t UTF-8 Extract2\$GameDir$\Localization\eng\MK10Game.eng>LANGFILE.txt
start /wait Scripts\NoNullE.exe
copy noNull.txt LANGFILE.txt >nul
del NoNull.txt 2>nul
cls
echo Done Modifying!

