del LocalStaticVariables.obj
del LocalStaticVariables.exe

cl.exe /c /EHsc LocalStaticVariables.c

link.exe LocalStaticVariables.obj

LocalStaticVariables.exe
