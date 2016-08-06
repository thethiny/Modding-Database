@echo off
title Package Cloner
md Output 2>nul
md Output\Asset 2>nul
md Output\MKScript 2>nul
md PackageFiles 2>nul
del /Q name.txt 2>nul
del /Q name2.txt 2>nul
echo.If you get File Not Found please make sure all files are there...
echo.Type 0 at any time to stop
echo.Usage Example:
echo.If you are are Cloning Subzero_C into Subzero_D, then please type Subzero_C:
:LOOP
set /p name=Type CHAR_COSTUME: 
if /I "%name%" EQU "0" goto :Resume
echo.%name%>>name.txt
echo. 
echo.Decompressing Files...
decompress.exe Files\Content\CHAR_%name%.xxx >nul
decompress.exe Files\Content\CHAR_%name%_SCRIPTASSETS.xxx >nul
decompress.exe Files\Content\DISM_%name%.xxx >nul
decompress.exe Files\Content\DISM_%name%_DLC.xxx >nul
move unpacked\CHAR_%name%.xxx PackageFiles >nul
move unpacked\CHAR_%name%_SCRIPTASSETS.xxx PackageFiles >nul
move unpacked\DISM_%name%.xxx PackageFiles >nul
move unpacked\DISM_%name%_DLC.xxx PackageFiles 2>nul
copy Files\Content\CHAR_%name%.mko PackageFiles\CHAR_%name%.mko >nul
echo Done...
cls
echo type 0 to stop multi tool:
goto :Loop

:Resume
cls
echo.Starting PackageCloner.exe
start /wait Scripts\PackageCloner.exe
move *.xxx Output\Asset
move *.mko Output\MKScript
move *.tfc Output\Asset
del /Q name.txt 2>nul
RMDIR /S /Q unpacked
RMDIR /S /Q PackageFiles
del /Q Files\Content\*
cls
echo.Starting CHARSETADDER.exe
start /wait Scripts\CHARSETADDER.exe
copy Modded.ini Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
call scripts\CRepack.bat
RMDIR /S /Q Extract
del /Q name2.txt 2>nul
del /Q Modded.ini 2>nul
del /Q names 2>nul
cls
echo.Copy the files inside Output\ to your Game's directory :D
echo.And I deleted your Files\Content because I know that you will forget :P
echo.Yes you need to copy them again the next time -_-
echo.Don't forget to replace the Files\ to update your game the next time
pause