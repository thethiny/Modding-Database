@echo off
title Story Pack Installer
echo.===========================
echo.Story Pack Installer by thethiny
echo.Special Thanks to UncleFestor and CynicalHippie
echo.===========================
echo.Make sure to have this installer in the Game's Directory!
echo.X64TOC.txt must be in the same folder
echo.Coalesced.ini must be in "Config"
echo.Coalesced.ENG must be in "Localization"
echo.Make sure that you extracted CharData.7z, MKO.7z and UI.7z.
echo.You must have the 3 Folders (MKOs CharPacks UI) in the same location as the X64TOC.txt
echo.Press any key to start the installer..
pause >nul
md Asset 2>nul
md MKScript 2>nul
cls
echo.Copying Required Files...
copy Asset\Char_Shinnok_A.tfc Asset\CHAR_CorShnk_A.tfc
copy Asset\DISM_Shinnok_A_DLC.tfc Asset\CHAR_CorShnk_A_DLC.tfc
copy Asset\Shinnok_CharIntro.tfc Asset\CorShnk_CharIntro.tfc
copy Asset\Sindel_A.xxx Asset\CHAR_Sindel_A.xxx
copy Asset\Sindel_A_SCRIPTASSETS.xxx Asset\CHAR_Sindel_A_SCRIPTASSETS.xxx
copy Asset\Rain_A_SCRIPTASSETS.xxx Asset\Char_Rain_A_SCRIPTASSETS.xxx
copy Asset\Baraka_A.xxx Asset\CHAR_Baraka_A.xxx
copy Asset\Baraka_A.tfc Asset\CHAR_Baraka_A.tfc
copy Asset\Baraka_A_SCRIPTASSETS.xxx Asset\CHAR_Baraka_A_SCRIPTASSETS.xxx
copy MKScript\ShinnokBoss_A.mko MKScript\CorShnk_A.mko
cls
echo.Installing UI Files...
md Asset\BACKUPED-SKP
copy UI\LoadScreen_Rain_A.xxx Asset\LoadScreen_Rain_A.xxx
copy UI\LoadScreen_Baraka_A.xxx Asset\LoadScreen_Baraka_A.xxx
copy UI\LoadScreen_Sindel_A.xxx Asset\LoadScreen_Sindel_A.xxx
copy UI\LoadScreen_CorShnk_A.xxx Asset\LoadScreen_CorShnk_A.xxx
copy Asset\ui_ps_CharGrid_DLC.xxx Asset\BACKUPED-SKP\ui_ps_CharGrid_DLC.xxx
copy UI\ui_ps_CharGrid_DLC.xxx Asset\ui_ps_CharGrid_DLC.xxx
copy Asset\ui_ps_Versus_Jpegs_LinKuei_DLC.xxx Asset\BACKUPED-SKP\ui_ps_Versus_Jpegs_LinKuei_DLC.xxx
copy Asset\ui_ps_Single_Jpegs_LinKuei_DLC.xxx Asset\BACKUPED-SKP\ui_ps_Single_Jpegs_LinKuei_DLC.xxx
copy Asset\ui_ps_Versus_Jpegs_BroShad_DLC.xxx Asset\BACKUPED-SKP\ui_ps_Versus_Jpegs_BroShad_DLC.xxx
copy Asset\ui_ps_Single_Jpegs_BroShad_DLC.xxx Asset\BACKUPED-SKP\ui_ps_Single_Jpegs_BroShad_DLC.xxx
copy Asset\ui_ps_Versus_Jpegs_SpeForc_DLC.xxx Asset\BACKUPED-SKP\ui_ps_Versus_Jpegs_SpeForc_DLC.xxx
copy Asset\ui_ps_Single_Jpegs_SpeForc_DLC.xxx Asset\BACKUPED-SKP\ui_ps_Single_Jpegs_SpeForc_DLC.xxx
copy Asset\ui_ps_Versus_Jpegs_WhiLotu_DLC.xxx Asset\BACKUPED-SKP\ui_ps_Versus_Jpegs_WhiLotu_DLC.xxx
copy Asset\ui_ps_Single_Jpegs_WhiLotu_DLC.xxx Asset\BACKUPED-SKP\ui_ps_Single_Jpegs_WhiLotu_DLC.xxx
copy Asset\ui_ps_Versus_Jpegs_BlaDrag_DLC.xxx Asset\BACKUPED-SKP\ui_ps_Versus_Jpegs_BlaDrag_DLC.xxx
copy Asset\ui_ps_Single_Jpegs_BlaDrag_DLC.xxx Asset\BACKUPED-SKP\ui_ps_Single_Jpegs_BlaDrag_DLC.xxx
cls
echo.Installing UI Files...
copy UI\ui_ps_Single_Jpegs_LinKuei_DLC.xxx Asset\ui_ps_Single_Jpegs_LinKuei_DLC.xxx
copy UI\ui_ps_Single_Jpegs_LinKuei_DLC.xxx ui_ps_Single_Jpegs_BroShad_DLC.xxx
copy UI\ui_ps_Single_Jpegs_LinKuei_DLC.xxx ui_ps_Single_Jpegs_SpeForc_DLC.xxx
copy UI\ui_ps_Single_Jpegs_LinKuei_DLC.xxx ui_ps_Single_Jpegs_WhiLotu_DLC.xxx
copy UI\ui_ps_Single_Jpegs_LinKuei_DLC.xxx ui_ps_Single_Jpegs_BlaDrag_DLC.xxx

copy UI\ui_ps_Versus_Jpegs_LinKuei_DLC.xxx Asset\ui_ps_Versus_Jpegs_LinKuei_DLC.xxx
copy UI\ui_ps_Versus_Jpegs_LinKuei_DLC.xxx ui_ps_Versus_Jpegs_BroShad_DLC.xxx
copy UI\ui_ps_Versus_Jpegs_LinKuei_DLC.xxx ui_ps_Versus_Jpegs_SpeForc_DLC.xxx
copy UI\ui_ps_Versus_Jpegs_LinKuei_DLC.xxx ui_ps_Versus_Jpegs_WhiLotu_DLC.xxx
copy UI\ui_ps_Versus_Jpegs_LinKuei_DLC.xxx ui_ps_Versus_Jpegs_BlaDrag_DLC.xxx

move ui_ps_*.xxx Instas\
cd Instas

start /wait MKKEGenericRenamer.exe "ui_ps_Single_Jpegs_BlaDrag_DLC.xxx" "LinKuei" "BlaDrag"
start /wait MKKEGenericRenamer.exe "ui_ps_Single_Jpegs_BroShad_DLC.xxx" "LinKuei" "BroShad"
start /wait MKKEGenericRenamer.exe "ui_ps_Single_Jpegs_WhiLotu_DLC.xxx" "LinKuei" "WhiLotu"
start /wait MKKEGenericRenamer.exe "ui_ps_Single_Jpegs_SpeForc_DLC.xxx" "LinKuei" "SpeForc"

start /wait MKKEGenericRenamer.exe "ui_ps_Versus_Jpegs_BlaDrag_DLC.xxx" "LinKuei" "BlaDrag"
start /wait MKKEGenericRenamer.exe "ui_ps_Versus_Jpegs_BroShad_DLC.xxx" "LinKuei" "BroShad"
start /wait MKKEGenericRenamer.exe "ui_ps_Versus_Jpegs_WhiLotu_DLC.xxx" "LinKuei" "WhiLotu"
start /wait MKKEGenericRenamer.exe "ui_ps_Versus_Jpegs_SpeForc_DLC.xxx" "LinKuei" "SpeForc"

cd ..\
move Instas\ui_ps_*.xxx ""

copy ui_ps_single_jpegs_BlaDrag_DLC.xxx Asset\UI_PS_SINGLE_JPEGS_BLADRAG_DLC.xxx
copy ui_ps_single_jpegs_BROSHAD_DLC.xxx Asset\UI_PS_SINGLE_JPEGS_BROSHAD_DLC.xxx
copy ui_ps_single_jpegs_WHILOTU_DLC.xxx Asset\UI_PS_SINGLE_JPEGS_WHILOTU_DLC.xxx
copy ui_ps_single_jpegs_SPEFORC_DLC.xxx Asset\UI_PS_SINGLE_JPEGS_SPEFORC_DLC.xxx

copy ui_ps_VERSUS_jpegs_BlaDrag_DLC.xxx Asset\UI_PS_VERSUS_JPEGS_BLADRAG_DLC.xxx
copy ui_ps_VERSUS_jpegs_BROSHAD_DLC.xxx Asset\UI_PS_VERSUS_JPEGS_BROSHAD_DLC.xxx
copy ui_ps_VERSUS_jpegs_WHILOTU_DLC.xxx Asset\UI_PS_VERSUS_JPEGS_WHILOTU_DLC.xxx
copy ui_ps_VERSUS_jpegs_SPEFORC_DLC.xxx Asset\UI_PS_VERSUS_JPEGS_SPEFORC_DLC.xxx

del /Q ui_ps_*_DLC.xxx 2>nul

cls
echo.Installing Packages...
copy CharPacks\*.xxx Asset\
echo. 
echo.Installing Scripts...
copy MKOs\*.mko MKScript\
cls
echo.Installing Files Finished.
echo.Patching ini/eng/txt...
call Instas\PatcherX64.bat
call Instas\PatcherIni.bat
call Instas\PatcherLang.bat
cls
echo.ALL FILES HAVE BEEN BACKUPED
pause