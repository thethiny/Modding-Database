@echo off
echo.Place ALL the files inside a folder in this structure:
echo.    FILENAME.mp4_folder
echo.Example:
echo.    2016090802.mp4_folder
echo.For best outcome, make sure the file's extension is .mp4
echo.You will need:
echo.KHUxEncrypt
echo.AppendBGAD
echo.KHUxDecrypt
echo. 
echo.There's a log file at the end called "MP4Repack.log"
echo. 
set /p fname="Enter MP4 file to repack: "
khuxdecrypt %fname% 0_NotNeeded_0 > %fname%.txt
echo.Repacking %fname%... > MP4+PNGRepack.log
MP4Repack %fname% >> MP4+PNGRepack.log
echo. 
echo.If everything is fine, you will find
echo.    %fname%_out
del /S /Q %fname%.txt > nul
RMDIR /S /Q 0_NotNeeded_0
set fname=%fname:~0,-3%
set fname=%fname%png
echo.
echo.Attempting to fix %fname%
echo.
start /wait khuxdecrypt %fname% %fname%_folder
echo. >> MP4+PNGRepack.log
echo. >> MP4+PNGRepack.log
echo. >> MP4+PNGRepack.log
echo.Start of PNG... >> MP4+PNGRepack.log
echo. >>MP4+PNGRepack.log
echo. >>MP4+PNGRepack.log
pngFIX %fname% 1 >>MP4+PNGRepack.log
echo.Done!
ren %fname%_list @nonameFix.bin
move @nonameFix.bin %fname%_folder >nul
del %fname%_folder\@noname1.bin
cd %fname%_folder
start /wait ..\khuxencrypt @nonameFix.bin /
start /wait ..\khuxencrypt md5
start /wait ..\khuxencrypt size
cd ..\
echo. 2>%fname%_out
start /wait appendbgad %fname%_out %fname%_folder\@nonameFix.bin.BGAD %fname%_folder\md5.bgad %fname%_folder\size.bgad
del %fname%_out
ren %fname%_out_out %fname%_out
RMDIR /S /Q %fname%_folder
echo If everything went fine here, you'll find %fname%_out.
pause