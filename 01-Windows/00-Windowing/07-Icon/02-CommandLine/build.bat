del resource.res

del MyWindowWithIcon.obj

del MyWindowWithIcon.exe

cl.exe /c /EHsc MyWindowWithIcon.cpp

rc resource.rc 

link.exe MyWindowWithIcon.obj resource.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS

MyWindowWithIcon.exe