@echo off
echo.Place ALL the files inside a folder in this structure:
echo.    FILENAME.mp4_folder
echo.Example:
echo.    2016090802.mp4_folder
echo. 
echo.There's a log file at the end called "MP4Repack.log"
echo. 
set /p fname="Enter MP4 file to repack: "
khuxdecrypt %fname% 0_NotNeeded_0 > %fname%.txt
echo.Repacking %fname%... > MP4Repack.log
MP4Repack %fname% >> MP4Repack.log
echo. 
echo.If everything is fine, you will find
echo.    %fname%_out
del /S /Q %fname%.txt > nul
RMDIR /S /Q 0_NotNeeded_0
pause > nul