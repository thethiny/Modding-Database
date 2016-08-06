@echo off
title DLC Uninstaller
echo.Make sure the files are in Files\
echo.==============================
echo.  -COALESCED.INI
echo.  -COALESCED.ENG
echo.==============================
echo. 
set /p lng=PRESS Enter for English, Press 0 then Enter for NonEnglish: 
RMDIR /S /Q Extract 2>nul
RMDIR /S /Q Extract2 2>nul
call Scripts\CExtract.bat
call Scripts\EExtract_M.bat
call Scripts\NoNULL_INI.bat
del noNull.txt 2>Nul
if /I "%lng%" EQU "0" goto :MULTI
cls
echo.Loading COALSCED.ENG...
Scripts\iconv -f UNICODELITTLE -t UTF-8 Extract2\$GameDir$\Localization\eng\MK10Game.eng>LANGFILE.txt
start /wait Scripts\NoNullE.exe
copy noNull.txt LANGFILE.txt >nul
del NoNull.txt 2>nul
cls
echo Done Modifying!


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
:END
RMDIR /S /Q Extract 2>nul
RMDIR /S /Q Extract2 2>nul
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
exit



:MULTI
cls
echo.
echo.Languages     3 Letters
echo.ENGLISH       ENG
echo.ESPERANTO     ESP
echo.FRENCH        FRA
echo.GERMAN        GER
echo.ITALIAN       ITA
echo.POLISH        POL
echo.PORTUGUESE    POR
echo.RUSSIAN       RUS
echo.SPANISH       SPA
set /p fl=Enter Language's 3 Letters (ex: RUS):

echo.Loading COALSCED.ENG...
Scripts\iconv -f UNICODELITTLE -t UTF-8 Extract2\$GameDir$\Localization\%fl%\MK10Game.%fl%>LANGFILE.txt
start /wait Scripts\NoNullE.exe
copy noNull.txt LANGFILE.txt >nul
del NoNull.txt 2>nul
cls
echo Done Modifying!
cls
start /wait Scripts\DLCRemover.exe
copy UnSetMK10.ini Extract\$StartupCacheDir$\Config\X64-MK10Game.ini >nul
Scripts\iconv -f UTF-8 -t UNICODELITTLE UnIndLang.txt>Extract2\$GameDir$\Localization\%fl%\MK10Game.%fl%
del /Q UnIndMK10.ini 2>nul
del /Q UnSetMK10.ini 2>nul
del /Q LANGFILE.txt 2>nul
del /Q UnIndLang.txt 2>nul
call Scripts\CRepack.bat
call Scripts\ERepack_M.bat
cls
RMDIR /S /Q Extract
RMDIR /S /Q Extract2
cd Output\Localization
ren COALESCED.ENG Coalesced.%fl%
cd ..\..\
cls
goto :END