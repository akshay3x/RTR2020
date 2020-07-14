del BlueWindow.obj 

del BlueWindow.exe

del resource.res


cl.exe /c /EHsc BlueWindow.cpp

rc resource.rc 

link.exe BlueWindow.obj resource.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS

BlueWindow.exe