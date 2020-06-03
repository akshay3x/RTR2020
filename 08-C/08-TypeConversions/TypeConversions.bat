del TypeConversions.obj
del TypeConversions.exe
cl.exe /c /EHsc TypeConversions.c

link.exe TypeConversions.obj

TypeConversions.exe
