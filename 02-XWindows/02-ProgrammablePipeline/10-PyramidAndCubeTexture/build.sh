rm -f xwindow
g++ -o xwindow xwindow.cpp -lX11 -lGL -Wall -lGLU -lGLEW -L/usr/lib64 -lSphere -lSOIL
