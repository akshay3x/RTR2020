del SimpleLoop_Break.obj
del SimpleLoop_Break.exe

cl.exe /c /EHsc SimpleLoop_Break.c

link.exe SimpleLoop_Break.obj

SimpleLoop_Break.exe
