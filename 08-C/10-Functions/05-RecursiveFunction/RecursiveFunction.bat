del RecursiveFunction.obj
del RecursiveFunction.exe

cl.exe /c /EHsc RecursiveFunction.c

link.exe RecursiveFunction.obj

RecursiveFunction.exe
