@echo off & setlocal EnableDelayedExpansion
del noNull.txt >Nul
cls
echo.Loading File 3...
Scripts\iconv -f UNICODELITTLE -t UTF-8 Extract2\$GameDir$\Localization\eng\MK10Game.eng>LANGFILE.txt
start /wait Scripts\NoNullE.exe
copy noNull.txt LANGFILE.txt >nul
del NoNull.txt >nul
cls
echo Done Modifying!

