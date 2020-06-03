del SimpleLoop_Continue.obj
del SimpleLoop_Continue.exe

cl.exe /c /EHsc SimpleLoop_Continue.c

link.exe SimpleLoop_Continue.obj

SimpleLoop_Continue.exe
