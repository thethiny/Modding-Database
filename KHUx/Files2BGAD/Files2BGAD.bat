@echo off
echo.Place all files into a folder
set /p fname="Enter a folder name to repack: "
set /p name="Enter the output file name: "
cd %fname%
cd > ..\Dir_Out.txt
dir /S /B /A:-D >> ..\Dir_Out.txt
cd ..\
echo.Repacking %fname%... > Repack.log
Files2BGAD.exe %fname% %name% >> Repack.log
echo. 
echo.If everything is fine, you will find %name%.
echo. 
del /S /Q Dir_Out.txt >nul
pause > nul