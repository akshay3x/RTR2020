
del meshLoading.obj
del meshLoading.dll
del meshLoading.exp
del meshLoading.lib

cl.exe /c /EHsc meshLoading.cpp
link.exe /DLL meshLoading.obj
