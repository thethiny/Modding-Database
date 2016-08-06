@ECHO OFF
md Extract
if ERRORLEVEL 2 echo error1
quickbms.exe -o Scripts\MK_10_text_binar.bms Files\Coalesced.ini Extract\
if ERRORLEVEL 1 echo error2
quickbms -o Scripts\MK_10_text_extract_all.bms Extract\Coalesced.ini Extract\
if ERRORLEVEL 1 echo error3
cls
echo DONE! Extracted