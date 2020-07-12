del MyOGL_Template.obj 

del MyOGL_Template.exe

del resource.res


cl.exe /c /EHsc MyOGL_Template.cpp

rc resource.rc 

link.exe MyOGL_Template.obj resource.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS

MyOGL_Template.exe