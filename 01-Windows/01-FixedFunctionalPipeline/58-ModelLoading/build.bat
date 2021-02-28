del main.obj 

del Application.exe

del resource.res

cl.exe /c /EHsc main.cpp 

rc resource.rc 

link.exe main.obj resource.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS /out:Application.exe
