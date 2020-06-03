del UserControlledInfiniteLoop.obj
del UserControlledInfiniteLoop.exe

cl.exe /c /EHsc UserControlledInfiniteLoop.c

link.exe UserControlledInfiniteLoop.obj

UserControlledInfiniteLoop.exe
