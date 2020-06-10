del MacroFunction.obj
del MacroFunction.exe

cl.exe /c /EHsc MacroFunction.c

link.exe MacroFunction.obj

MacroFunction.exe
