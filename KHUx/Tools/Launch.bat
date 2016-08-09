@echo off
md pngImages 2>nul
md DATS 2>nul
del pngList.txt 2>nul
cd Input
for %%f in (*.png) do (
md ..\Output\%%f_out 2>nul
echo %%f%>>..\pngList.txt
)
for %%f in (*.png) do (
..\offzip -a -z -15 -Q %%f ..\Output\%%f_out
ren ..\Output\%%f_out\*.dat %%f.dat >nul
move ..\Output\%%f_out\*.dat ..\DATS\ >nul
)
cd ..\
rmdir /s /q Output
start /wait KHUxPNG2BMP.exe
rmdir /s /q DATS
del pngList.txt 2>nul
cls
echo Your BMPs are in pngImages Folder.
pause >nul