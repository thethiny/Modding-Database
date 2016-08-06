@echo off
title X64TOC Patcher
del X64_Dec.txt 2>nul
copy X64TOC.txt X64_Dec.txt >nul
copy X64TOC.txt X64TOC_BackupSKP.txt
Instas\AES_X64.exe -d X64_Dec.txt
start /wait Instas\NoNullX64.exe
copy noNull.txt X64_Dec.txt >nul
del noNull.txt 2>nul

echo.0 0 0 0 11 ..\Asset\CHAR_Rain_A.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\CHAR_Rain_A_SCRIPTASSETS.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\DISM_Rain_A.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\DISM_Rain_A_DLC.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\UI_PS_Rain_SCRIPTASSETS.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\MKScript\CHAR_Rain_A.mko 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\MKScript\CHAR_Rain_A.module 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\MKScript\CHAR_Rain_A.tweak 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\MKScript\UI_PS_Rain.mko 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\MKScript\UI_PS_Rain.module 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\Loadscreen_rain_a.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\CHAR_Sindel_A.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\CHAR_Sindel_A_SCRIPTASSETS.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\UI_PS_SINDEL_SCRIPTASSETS.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\MKScript\UI_PS_Sindel.mko 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\MKScript\UI_PS_Sindel.module 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\Sindel_CharIntro.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\Sindel_CharIntro_MapAssets.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\LoadScreen_Sindel_A.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\CHAR_Baraka_A.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\CHAR_Baraka_A.tfc 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\CHAR_Baraka_A_SCRIPTASSETS.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\UI_PS_Baraka_SCRIPTASSETS.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\MKScript\UI_PS_Baraka.mko 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\MKScript\UI_PS_Baraka.module 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\Baraka_CharIntro.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\Baraka_CharIntro_MapAssets.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\LoadScreen_Baraka_A.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\CHAR_CorShnk_A.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\CHAR_CorShnk_A_SCRIPTASSETS.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\UI_PS_CorShnk_SCRIPTASSETS.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\MKScript\UI_PS_CorShnk.mko 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\MKScript\UI_PS_CorShnk.module 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\MKScript\CorShnk_A.mko 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\MKScript\CorShnk_A.module 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\MKScript\CorShnk_A.tweak 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\CorShnk_CharIntro.tfc 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\CorShnk_CharIntro.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\CorShnk_CharIntro_MapAssets.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\DISM_CorShnk_A.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\DISM_CorShnk_A_DLC.xxx 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\DISM_CorShnk_A_DLC.tfc 11>>X64_Dec.txt
echo.0 0 0 0 11 ..\Asset\LoadScreen_corshnk_a.xxx 11>>X64_Dec.txt
echo. >>X64_Dec.txt

copy X64_Dec.txt X64TOC.txt
del /Q X64_Dec.txt 2>nul
Instas\AES_X64.exe -e X64TOC.txt

cls

