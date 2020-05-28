del Constants.obj
del Constants.exe
cl.exe /c /EHsc Constants.c

link.exe Constants.obj

Constants.exe
