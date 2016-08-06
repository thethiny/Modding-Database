@echo off
title Ini Patcher

copy Config\Coalesced.ini Config\Coalesced_BackupSKP.ini
md Extract
Instas\quickbms.exe -o Instas\MK_10_text_binar.bms Config\Coalesced.ini Extract\
Instas\quickbms.exe -o Instas\MK_10_text_extract_all.bms Extract\Coalesced.ini Extract\
cls

del noNull.txt 2>Nul
start /wait Instas\noNull.exe
copy noNull.txt Extract\$StartupCacheDir$\Config\X64-MK10Game.ini >nul
del NoNull.txt >nul

echo. >>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.[MK10Game.MK10GameSettings]>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.mAOC=CHAR_Rain_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.mAOC=CHAR_Baraka_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.mAOC=CHAR_Sindel_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.mAOC=CHAR_CorShnk_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.[Unlocked.Characters]>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Unlocked=CHAR_Rain_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Unlocked=CHAR_Sindel_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Unlocked=CHAR_Baraka_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Unlocked=CHAR_CorShnk_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.[CharacterSettings.CHAR_Rain_A]>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.MeshName=Meshes.Rain_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_Male>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_Male_DLC>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_Rain_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_Rain_A_DLC>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.LadderRelief=UI_TWR_Reliefs_Kano_St>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.LaddderMic=UI_TWR_Reliefs_Wall_Kano_St>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Trait=TRAIT_Kenshi3>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Trait=TRAIT_Goro3>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Trait=TRAIT_Raiden3>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.PlayerSelectPkgSuffix=_DLC>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.[CharacterSettings.CHAR_Baraka_A]>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.MeshName=Meshes.Baraka_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_Male>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_Male_DLC>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_Baraka_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_Baraka_A_DLC>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.LadderRelief=UI_TWR_Reliefs_Kenshi_St>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.LaddderMic=UI_TWR_Reliefs_Wall_Kenshi_St>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Trait=TRAIT_Shinnok1>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Trait=TRAIT_Shinnok2>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Trait=TRAIT_Shinnok3>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.PlayerSelectPkgSuffix=_DLC>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.[CharacterSettings.CHAR_Sindel_A]>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.MeshName=Meshes.Sindel_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_Female>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_Female_DLC>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_Sindel_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_Sindel_A_DLC>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.LadderRelief=UI_TWR_Reliefs_Kitana_St>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.LaddderMic=UI_TWR_Reliefs_Wall_Kitana_St>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Trait=TRAIT_Kitana1>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Trait=TRAIT_Kitana2>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Trait=TRAIT_CageJr1>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.PlayerSelectPkgSuffix=_DLC>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.[CharacterSettings.CHAR_CorShnk_A]>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.MeshName=Meshes.ShinnokBoss_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_ShokanMale>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_ShokanMale_DLC>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_CorShnk_A>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Dismemberment=DISM_CorShnk_A_DLC>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.LadderRelief=UI_TWR_Reliefs_Shinnok_St>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.LaddderMic=UI_TWR_Reliefs_Wall_Shinnok_St>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Trait=TRAIT_Shinnok1>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Trait=TRAIT_Shinnok2>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.Trait=TRAIT_Shinnok3>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.PlayerSelectPkgSuffix=_DLC>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.[CharacterKeys]>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.CHAR_CorShnk_A=SH>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.CHAR_Baraka_A=BA>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.CHAR_Sindel_A=SI>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo.CHAR_Rain_A=RN>>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini
echo. >>Extract\$StartupCacheDir$\Config\X64-MK10Game.ini

cls

Instas\quickbms.exe -o Instas\MK_10_text_repack_ini.bms Extract\Coalesced.ini Extract\
if ERRORLEVEL 1 (
	echo -------------------------------------
	echo Error repacking Extract\Coalesced.ini
	pause
	exit 
) 
cls
echo Repacking Extract\Coalesced.ini Done!
copy Extract\Coalesced.ini Config\Coalesced.ini
start /wait Instas\AES_C.exe -e Config\Coalesced.ini
if ERRORLEVEL 1 (
	echo Error Encrypting
	pause
	exit 
) 
echo Encoding Extract\Coalesced.ini Done!
echo Config\Coalesced.ini is ready
RMDIR /S /Q Extract\
cls

