del StringByString.obj
del StringByString.exe

cl.exe /c /EHsc StringByString.c

link.exe StringByString.obj

StringByString.exe
