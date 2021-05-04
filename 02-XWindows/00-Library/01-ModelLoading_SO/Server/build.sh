rm -f mylib.obj
rm libmylib.so

g++  -c mylib.cpp -o mylib.obj -Wall -fPIC

g++  mylib.obj -shared -o libmylib.so

