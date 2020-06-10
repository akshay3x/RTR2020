del EntryPointFunction.obj
del EntryPointFunction.exe

cl.exe /c /EHsc EntryPointFunction.c

link.exe EntryPointFunction.obj

EntryPointFunction.exe 1 23 45
