@echo off
set /p name="Enter the name of the file: "
umodel -list %name% > %name%.txt
pause