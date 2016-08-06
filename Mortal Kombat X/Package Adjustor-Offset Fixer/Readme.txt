MKX Package Adjuster v 1.0.0 - Offset Modifier by thethiny
Special Thanks to UncleFestor
=========================


Required:

- Umodel
- Character Package
- Character Package File List (obtained with Umodel)
- Unreal Package Decompressor
- This tool and its DLLs


Usage:

- Start by taking your character package file (.xxx) and dragging it over the Decompressor, this will generate a decompressed package file.
- Take this decompressed package file and place it inside this folder and then run Mesh.bat.
- Type the name of the package without ".xxx".
- Now you must have CHAR_XXXXX_X.xxx and CHAR_XXXXX_X.txt (XXXXX is anything) in the same folder.
- Run PackageAdjuster.exe.
- Type in the name of the character you want without ".xxx" and hit Enter.
The tool will now fix your offsets so the game loads them fine.

Notes:
*This tool is designed to fix the offsets for swapped files inside packages. You need to open the txt file and search for the file you want to swap, convert the numbers you find to Little Endian and go to that offset, replace the bytes with bytes from other characters (or the file you want to swap). Keep track of the new byte size, if you changed 15 bytes to 10, then you will need to search for the offset you first found in Little Endian and replace the first four bytes with the new value.
*This tool will not actually replace the files, you must do that yourself, check UncleFestor's 1st Advanced modding tutorial for more info.
*This will not, and possible never will work with Material Swapped players as the offsets are swapped which confusing the hell out of this tool.

This tool is open-source for users who are willing to improve, and is directed towards advanced modders. If you didn't understand a step then probably this tool isn't for you.

