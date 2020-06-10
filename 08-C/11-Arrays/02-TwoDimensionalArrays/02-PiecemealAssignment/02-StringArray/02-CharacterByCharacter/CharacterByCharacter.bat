del CharacterByCharacter.obj
del CharacterByCharacter.exe

cl.exe /c /EHsc CharacterByCharacter.c

link.exe CharacterByCharacter.obj

CharacterByCharacter.exe
