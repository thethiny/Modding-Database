@echo off
title Language Patcher
echo.English		ENG
echo.Spanish		SPA
echo.French		FRA
echo.German		GER
echo.Italian		ITA
echo.Polish		POL
echo.Portuguese		POR
echo.Russian		RUS
echo.Esperanto		ESP
echo. 

set /p lname=Enter Your Langauge Name: 

copy Localization\COALESCED.%lname% Localization\COALESCED_BackupSKP.%lname%
md Extract
if ERRORLEVEL 2 echo error1
Instas\quickbms.exe -o Instas\MK_10_text_binar.bms Localization\Coalesced.%lname% Extract\
if ERRORLEVEL 1 echo error2
Instas\quickbms -o Instas\MK_10_text_extract_all.bms Extract\Coalesced.%lname% Extract\
if ERRORLEVEL 1 echo error3
cls
echo DONE! Extracted

del noNull.txt >Nul
cls
Instas\iconv -f UNICODELITTLE -t UTF-8 Extract\$GameDir$\Localization\%lname%\MK10Game.%lname%>LANGFILE.txt
start /wait Instas\NoNullE.exe
copy noNull.txt LANGFILE.txt >nul
del NoNull.txt >nul
cls

echo.; Story Kombat Pack by thethiny & UncleFestor>>LANGFILE.txt
echo.[PlayerSelect]>>LANGFILE.txt
echo.CHAR_Rain_A=RAIN>>LANGFILE.txt
echo.CHAR_Baraka_A=BARAKA>>LANGFILE.txt
echo.CHAR_Sindel_A=SINDEL>>LANGFILE.txt
echo.CHAR_CorShnk_A=CORRUPTED SHINNOK>>LANGFILE.txt
echo. >>LANGFILE.txt

Instas\iconv -f UTF-8 -t UNICODELITTLE LANGFILE.txt>Extract\$GameDir$\Localization\%lname%\MK10Game.%lname%

Instas\quickbms.exe -o Instas\MK_10_text_repack_lng.bms Extract\COALESCED.%lname% Extract\
if ERRORLEVEL 1 (
	echo -------------------------------------
	echo Error repacking Extract\Coalesced.ENG
	pause
	exit 
)
cls
echo Repacking Extract\Coalesced.%lname% Done!
copy Extract\COALESCED.%lname% Localization\Coalesced.%lname%
start /wait Instas\AES_C.exe -e Localization\Coalesced.%lname%
if ERRORLEVEL 1 (
	echo Error
	pause
	exit 
) 
echo Encoding Extract\Coalesced.%lname% Done!
echo Localization\Coalesced.%lname% is ready
RMDIR /S /Q Extract\ 2>nul
del /Q LANGFILE.txt 2>nul
