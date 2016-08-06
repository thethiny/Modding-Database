@ECHO OFF
md Extract2
if ERRORLEVEL 2 echo error1
quickbms.exe -o Scripts\MK_10_text_binar.bms Files\Coalesced.ENG Extract2\
if ERRORLEVEL 1 echo error2
quickbms -o Scripts\MK_10_text_extract_all.bms Extract2\Coalesced.ENG Extract2\
if ERRORLEVEL 1 echo error3
cls
echo DONE! Extracted
