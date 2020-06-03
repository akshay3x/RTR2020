del UserInputDependentIteration.obj
del UserInputDependentIteration.exe

cl.exe /c /EHsc UserInputDependentIteration.c

link.exe UserInputDependentIteration.obj

UserInputDependentIteration.exe
