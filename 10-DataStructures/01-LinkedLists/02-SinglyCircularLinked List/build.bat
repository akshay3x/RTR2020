
del main.obj 

del Application.exe

cl.exe /c /EHsc main.c

link.exe /out:Application.exe main.obj

Application.exe
