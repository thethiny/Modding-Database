@echo off
title Costume Adder
echo ====MKX Costume Adder====
echo =======by thethiny=======
echo.Special Thanks to UncleFestor, duc5, Injustice_AES Tool, quickbms, Coalscend Extractor/Repacker, The team behind WinGNU32, and Unreal Decompresser
echo. 
echo.Make sure all required files are in Files\
echo.==================
echo.-X64TOC.txt -REQUIRED
echo.-COALSCED.ini -REQUIRED
echo.-COALSCED.ENG -Only for Custom Naming
echo.
echo.This tool will create a new costume that has:
echo.====================================
echo.In-Game Name
echo.Player Select Screen Meshes
echo.====================================
echo.If you don't want a name,
echo.or if any file is missing,
echo.the tool will simply ignore it,
echo.like the COALSCED.ENG file.
echo.==================================== 
echo. 
set /p lng=Press Enter for English - Type 0 then Enter for NonEnglish: 
cls
if /I "%lng%" EQU "0" goto :MULTI

call "Scripts\CostumeAdderNoIC - MultiName.bat"
exit

:MULTI
call "Scripts\CostumeAdderNoIC - MultiLang.bat"
exit