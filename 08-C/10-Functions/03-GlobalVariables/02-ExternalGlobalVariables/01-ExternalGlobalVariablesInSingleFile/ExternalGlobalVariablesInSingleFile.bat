del ExternalGlobalVariablesInSingleFile.obj
del ExternalGlobalVariablesInSingleFile.exe

cl.exe /c /EHsc ExternalGlobalVariablesInSingleFile.c

link.exe ExternalGlobalVariablesInSingleFile.obj

ExternalGlobalVariablesInSingleFile.exe