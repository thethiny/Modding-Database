@echo off
echo.Costume Adder by thethiny
echo. 
echo.Make sure all required files are in Files\
echo.==================
echo.-X64TOC.txt
echo.-COALSCED.ini
echo.-COALESCED.ENG (RENAME YOUR COALSCED FILE to .ENG)
echo.
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
copy Files\X64TOC.txt X64_Dec.txt > Nul
AES_X64.exe -d X64_Dec.txt 
call Scripts\NoNullX64_M.bat
call Scripts\CExtract.bat
call Scripts\noNull_M.bat
call Scripts\EExtract_M.bat
Scripts\iconv -f UNICODELITTLE -t UTF-8 Extract2\$GameDir$\Localization\%fl%\MK10Game.%fl%>LANGFILE.txt
start /wait Scripts\NoNullE.exe
copy noNull.txt LANGFILE.txt >nul
del NoNull.txt 2>nul
cls
Start /wait Scripts\MultiLangWriter.exe
Scripts\iconv -f UTF-8 -t UNICODELITTLE ExtedLang.txt>Extract2\$GameDir$\Localization\%fl%\MK10Game.%fl%
del /Q LANGFILE.txt
del /Q ExtedLang.txt
cls
AES_X64.exe -e ExtedX64.txt
call Scripts\ERepack_M.bat
RMDIR /S /Q Extract2
cls
copy ExtedIni.ini Extract\$StartupCacheDir$\Config\X64-MK10Game.ini >nul
del /Q ExtedIni.ini 2>nul
copy ExtedX64.txt Output\X64TOC.txt >nul
del /Q X64_Dec.txt 2>nul
del /Q ExtedX64.txt 2>nul
cls
cd output\localization
ren Coalesced.eng Coalesced.%fl%
cd ..\..\
call Scripts\PackageCloner.bat
exit