del UserInputArrays.obj
del UserInputArrays.exe

cl.exe /c /EHsc UserInputArrays.c

link.exe UserInputArrays.obj

UserInputArrays.exe
