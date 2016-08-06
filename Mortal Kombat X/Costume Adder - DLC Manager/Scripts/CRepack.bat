@ECHO OFF

quickbms.exe -o Scripts\MK_10_text_repack_ini.bms Extract\Coalesced.ini Extract\
if ERRORLEVEL 1 (
	echo -------------------------------------
	echo Error repacking Extract\Coalesced.ini
	pause
	exit 
) 
cls
echo Repacking Extract\Coalesced.ini Done!
md Output 2>nul
md Output\Config 2>nul
copy Extract\Coalesced.ini Output\Config\Coalesced.ini
start "" AES_C.exe -e Output\Config\Coalesced.ini
if ERRORLEVEL 1 (
	echo Error
	pause
	exit 
) 
echo Encoding Extract\Coalesced.ini Done!
echo Output\Config\Coalesced.ini is ready