@shift
@echo off
title HackingToolkit3DS
mode con cols=100 lines=35
:TitleMenu
cls
echo.
echo    ##################################################
echo    #                                                #
echo    #            PackHack v4.8 by Asia81             #
echo    #               Edited by thethiny               #
echo    #              Updated: 03/15/2016               #
echo    #               asia81.webnode.fr                #
echo    #                                                #
echo    ##################################################
echo.
echo.
echo.
set /p NomD=CXI File No Extension: 
md %NomD%
echo.
ctrtool.exe -p --ncch=0 --exheader=%NomD%\ExHeader.bin --exefs=%NomD%\ExeFS.bin --romfs=%NomD%\RomFS.bin Dumps\%NomD%.cxi
echo.
ctrtool.exe -t romfs --romfsdir=%NomD%\RomFS_Ext %NomD%\RomFS.bin
echo.
pause
cls
echo.
set /p DecompressCode=Decompress the code.bin file (n/y) ?: 
if %DecompressCode%==y GOTO ExeFS2

:ExeFS1
cls
echo.
ctrtool.exe -t exefs --exefsdir=%NomD%\ExeFS_Ext %NomD%\ExeFS.bin
:EndIt
del %NomD%\ExeFS_Ext\.bin
echo.
copy %NomD%\ExeFS_Ext\banner.bin %NomD%\banner.bin
3dstool.exe -x -t banner -f %NomD%\banner.bin --banner-dir %NomD%\Banner_Ext\
ren %NomD%\Banner_Ext\banner0.bcmdl banner.cgfx
del %NomD%\banner.bin
echo.
echo Done!
echo.
pause
exit

:ExeFS2
cls
echo.
ctrtool.exe -t exefs --exefsdir=%NomD%\ExeFS_Ext %NomD%\ExeFS.bin --decompresscode
ren %NomD%\ExeFS_Ext\code.bin .code.bin
GOTO :EndIt