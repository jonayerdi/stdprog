@echo off

set output_dir=Debug_Win32
set sdllib=.\SDL2\lib\x64\SDL2.lib
set sdldll=.\SDL2\lib\x64\SDL2.dll
set includes=/Isrc /Isrc\target\win32 /ISDL2\include
set cfiles=.\src\*.c .\src\domain\*.c .\src\io\*.c .\src\lib\*.c .\src\target\win32\config\*.c .\src\target\win32\hal\*.c

mkdir %output_dir%

copy /Y parking_win32.json %output_dir%\parking.txt
copy /Y parking.bmp %output_dir%
copy /Y %sdldll% %output_dir%

vcvarsall & cl /nologo /W3 /D_CRT_SECURE_NO_WARNINGS /GS /Gd /GL /Za /Zi /Od /Ob0 /MTd /TC %includes% /Fo: %output_dir%\ /Fe: %output_dir%\parking_vga.exe /Fd: %output_dir%\parking_vga.pdb %cfiles% /link %sdllib% & del %output_dir%\*.obj
