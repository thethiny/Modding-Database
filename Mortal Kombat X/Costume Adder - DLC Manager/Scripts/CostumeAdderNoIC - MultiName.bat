@echo off
echo.Costume Adder by thethiny
echo. 
echo.Make sure all required files are in Files\
echo.==================
echo.-X64TOC.txt
echo.-COALSCED.ini
echo.-COASLCED.ENG
echo.
echo.
copy Files\X64TOC.txt X64_Dec.txt > Nul
AES_X64.exe -d X64_Dec.txt 
call Scripts\NoNullX64_M.bat
call Scripts\CExtract.bat
call Scripts\noNull_M.bat
call Scripts\EExtract_M.bat
call Scripts\noNullE_M.bat
Start /wait Scripts\MultiWriter.exe
Scripts\iconv -f UTF-8 -t UNICODELITTLE ExtedLang.txt>Extract2\$GameDir$\Localization\eng\MK10Game.eng
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
call Scripts\PackageCloner.bat
exit