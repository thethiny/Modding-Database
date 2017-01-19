@echo off
set /p name=Filename: 
call DecryptV2 %name% %name%_folder
call fileID %name%_folder
cls
echo Extracted and Fixed as much as possible
echo find output in %name%_folder
pause >nul