del IntegerArray.obj
del IntegerArray.exe

cl.exe /c /EHsc IntegerArray.c

link.exe IntegerArray.obj

IntegerArray.exe
