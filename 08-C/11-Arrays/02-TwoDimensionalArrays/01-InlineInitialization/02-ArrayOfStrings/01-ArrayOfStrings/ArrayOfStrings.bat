del ArrayOfStrings.obj
del ArrayOfStrings.exe

cl.exe /c /EHsc ArrayOfStrings.c

link.exe ArrayOfStrings.obj

ArrayOfStrings.exe
