@ECHO OFF
quickbms.exe -o Scripts\MK_10_text_repack_lng.bms Extract2\COALESCED.ENG Extract2\
if ERRORLEVEL 1 (
	echo -------------------------------------
	echo Error repacking Extract2\Coalesced.ENG
	pause
	exit 
)
cls
echo Repacking Extract2\Coalesced.ENG Done!
md Output 2>nul
md Output\Localization 2>nul
copy Extract2\COALESCED.ENG Output\Localization\Coalesced.ENG
start /wait "" AES_C.exe -e Output\Localization\Coalesced.ENG
if ERRORLEVEL 1 (
	echo Error
	pause
	exit 
) 
echo Encoding Extract2\Coalesced.ENG Done!
echo Output\Localization\Coalesced.ENG is ready