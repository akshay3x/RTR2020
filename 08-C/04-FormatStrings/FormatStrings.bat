del FormatStrings.obj
del FormatStrings.exe
cl.exe /c /EHsc FormatStrings.c

link.exe FormatStrings.obj

FormatStrings.exe
