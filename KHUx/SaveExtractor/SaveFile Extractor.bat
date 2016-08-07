@echo off
start /wait PrefsFile2Data.exe
start /wait khuxdecrypt Cocos2dxPrefsFile.xml.BGAD ExtractedSave\
start /wait khuxdecrypt ExtractedSave\purchase_transactions ExtractedSave\Purchaes_Transaction_Extracted\
start /wait khuxdecrypt ExtractedSave\tracking_events ExtractedSave\Tracking_Events_Extracted\
echo Done, your extracted files are in
echo ExtractedSave
echo purchase_transactions has been extracted as well
echo tracking_events has been extracted as well
echo ___________________
echo special thanks to XeNTaX users:
echo MayBeePha - BGAD Files
echo GovanifY - BGAD File Names
echo and thethiny (me) - SaveFile Extractor
pause >nul