@echo off 
set /p fname="Enter File to Open: "
KhuxDecrypt %fname% %fname%_temp > ContentsListing.txt
start /wait listing.exe
RMDIR /S /Q %fname%_temp
del /S /Q ContentsListing.txt
