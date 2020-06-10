del CharacterArray.obj
del CharacterArray.exe

cl.exe /c /EHsc CharacterArray.c

link.exe CharacterArray.obj

CharacterArray.exe
