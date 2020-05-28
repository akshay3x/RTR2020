del HelloWorld.obj
del HelloWorld.exe
cl.exe /c /EHsc HelloWorld.c

link.exe HelloWorld.obj

HelloWorld.exe
