del ExternalGlobalVariablesInMultipleFiles.obj
del File_01.obj
del File_02.obj

del ExternalGlobalVariablesInMultipleFiles.exe

cl.exe /c /EHsc ExternalGlobalVariablesInMultipleFiles.c File_01.c File_02.c

link.exe /out:ExternalGlobalVariablesInMultipleFiles.exe ExternalGlobalVariablesInMultipleFiles.obj File_01.obj File_02.obj

ExternalGlobalVariablesInMultipleFiles.exe
