del Variables.obj
del Variables.exe
cl.exe /c /EHsc Variables.c

link.exe Variables.obj

Variables.exe
