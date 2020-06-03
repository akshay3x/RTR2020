del NestedLoop_Break.obj
del NestedLoop_Break.exe

cl.exe /c /EHsc NestedLoop_Break.c

link.exe NestedLoop_Break.obj

NestedLoop_Break.exe
