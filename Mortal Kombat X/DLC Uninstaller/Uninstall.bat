@echo off
title DLC Uninstaller
echo.Make sure the files are in Files\
echo.==============================
echo.  -COALESCED.INI
echo.  -COALESCED.ENG
echo.==============================
echo. 
echo.PRESS ANY KEY TO START!
pause >nul
RMDIR /S /Q Extract 2>nul
RMDIR /S /Q Extract2 2>nul
call Scripts\CExtract.bat
call Scripts\EExtract_M.bat
call Scripts\NoNULL_INI.bat
call Scripts\NoNULL_ENG.bat
cls
start /wait Scripts\DLCRemover.exe
copy UnSetMK10.ini Extract\$StartupCacheDir$\Config\X64-MK10Game.ini >nul
Scripts\iconv -f UTF-8 -t UNICODELITTLE UnIndLang.txt>Extract2\$GameDir$\Localization\eng\MK10Game.eng
del /Q UnIndMK10.ini 2>nul
del /Q UnSetMK10.ini 2>nul
del /Q LANGFILE.txt 2>nul
del /Q UnIndLang.txt 2>nul
call Scripts\CRepack.bat
call Scripts\ERepack_M.bat
cls
RMDIR /S /Q Extract
RMDIR /S /Q Extract2
echo.====================================
echo.THANK YOUR FOR USING MY TOOL
echo.		                -thethiny
echo.====================================
echo.Copy the contents of Output\ to your game's directory.
echo."ALWAYS BACKUP YOUR FILES!" - A guy with a brain
echo."Don't forget to place the new ini/eng in the Files\ folder each time" -UncleFestor
echo.====================================
echo.Press Any Key to close (or the [x])...
pause >nul