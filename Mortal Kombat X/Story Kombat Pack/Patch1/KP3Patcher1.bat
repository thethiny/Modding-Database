@echo off
title Story Pack Installer Patch 1
echo.===========================
echo.Make sure to have this installer in the Game's Directory!
echo.X64TOC.txt must be in the same folder
echo.You must have the Folder AssetData in the same location as the X64TOC.txt
echo.Press any key to start the installer..
pause >nul
cls
echo.Creating Backups...
md Asset\BACKED-P1
copy Asset\ui_ps_Versus_Jpegs_BroShad_DLC.xxx Asset\BACKED-P1\ui_ps_Versus_Jpegs_BroShad_DLC.xxx
copy Asset\ui_ps_Single_Jpegs_BroShad_DLC.xxx Asset\BACKED-P1\ui_ps_Single_Jpegs_BroShad_DLC.xxx
copy Asset\ui_ps_Versus_Jpegs_SpeForc_DLC.xxx Asset\BACKED-P1\ui_ps_Versus_Jpegs_SpeForc_DLC.xxx
copy Asset\ui_ps_Single_Jpegs_SpeForc_DLC.xxx Asset\BACKED-P1\ui_ps_Single_Jpegs_SpeForc_DLC.xxx
copy Asset\ui_ps_Versus_Jpegs_WhiLotu_DLC.xxx Asset\BACKED-P1\ui_ps_Versus_Jpegs_WhiLotu_DLC.xxx
copy Asset\ui_ps_Single_Jpegs_WhiLotu_DLC.xxx Asset\BACKED-P1\ui_ps_Single_Jpegs_WhiLotu_DLC.xxx
copy Asset\ui_ps_Versus_Jpegs_BlaDrag_DLC.xxx Asset\BACKED-P1\ui_ps_Versus_Jpegs_BlaDrag_DLC.xxx
copy Asset\ui_ps_Single_Jpegs_BlaDrag_DLC.xxx Asset\BACKED-P1\ui_ps_Single_Jpegs_BlaDrag_DLC.xxx
copy Asset\ui_ps_Versus_Jpegs_DLC.xxx Asset\BACKED-P1\ui_ps_Versus_Jpegs_DLC.xxx
copy Asset\ui_ps_Single_Jpegs_DLC.xxx Asset\BACKED-P1\ui_ps_Single_Jpegs_DLC.xxx
ping localhost -n 2 >Nul
cls
echo.Installing Files...
copy AssetData\*.xxx Asset\
copy CharPacks\*.tfc Asset\
ping localhost -n 2 >nul
echo.Installing Files Finished.
echo.Patching X64TOC.txt...
call Instas\PatcherX64.bat
cls
echo.FILE BACKUPS ARE IN Asset\BACKED-P1
echo.Installed Succesfully
pause
rmdir /S /Q AssetData
