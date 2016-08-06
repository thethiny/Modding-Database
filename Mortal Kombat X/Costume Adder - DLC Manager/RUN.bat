@echo off
Title MKX DLC Manager
echo.==================================================================
echo.	Please Select One of the Following Options:
echo. 
echo.(Default) 0-Install DLC SKIN
echo.	  1-Install DLC Character
echo.	  2-Uninstall DLC
echo. 
echo.==================================================================
set /p choice=Enter number of choice: 
cls
if /I "%choice%" EQU "2" goto :TWO
if /I "%choice%" EQU "1" goto :ONE
if /I "%choice%" EQU "0" goto :ZERO

:ZERO
call Scripts\InstallDLC.bat
exit

:ONE
Title Coming Soon
echo.One day.... One day...
echo.:'       (
ping localhost -n 1 -w 300 >nul
cls
echo.One day.... One day...
echo.: '      (
ping localhost -n 1 -w 300 >nul
cls
echo.One day.... One day...
echo.:  '     (
ping localhost -n 1 -w 300 >nul
cls
echo.One day.... One day...
echo.:   '    (
ping localhost -n 1 -w 300 >nul
cls
echo.One day.... One day...
echo.:    '   (
ping localhost -n 1 -w 300 >nul
cls
echo.One day.... One day...
echo.:     '  (
ping localhost -n 1 -w 300 >nul
cls
echo.One day.... One day...
echo.:      ' (
ping localhost -n 1 -w 300 >nul
cls
echo.One day.... One day...
echo.:       '(
ping localhost -n 1 -w 300 >nul
cls
goto :ONE

:TWO
call Scripts\UninstallDLC.bat
exit
