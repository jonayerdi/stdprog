@echo off

set output_dir=Debug_win32
set sdllib=..\SDL2\lib\x86\SDL2.lib
set sdldll=..\SDL2\lib\x86\SDL2.dll
set includes=/I..\src /I..\src\target\win32 /I..\SDL2\include /I..\SDL2\include /I..\Unity-2.4.3\src /I..\Unity-2.4.3\extras\fixture\src
set cfiles=..\src\test\*.c ..\src\domain\*.c ..\src\io\*.c ..\src\lib\*.c ..\src\target\win32\config\*.c ..\src\target\win32\hal\*.c ..\Unity-2.4.3\src\unity.c ..\Unity-2.4.3\extras\fixture\src\unity_fixture.c *.c

mkdir %output_dir%

copy /Y test.json %output_dir%\test.txt
copy /Y parking.bmp %output_dir%
copy /Y %sdldll% %output_dir%

vcvarsall & cl /nologo /W3 /D_CRT_SECURE_NO_WARNINGS /F 2097152 /GS /Gd /GL /Zi /Od /Ob0 /MTd /TC %includes% /Fo: %output_dir%\ /Fe: %output_dir%\apparking_test.exe /Fd: %output_dir%\apparking_test.pdb %cfiles% /link %sdllib% & del %output_dir%\*.obj
