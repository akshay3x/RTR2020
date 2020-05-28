del EscapeSequences.obj
del EscapeSequences.exe
cl.exe /c /EHsc EscapeSequences.c

link.exe EscapeSequences.obj

EscapeSequences.exe
