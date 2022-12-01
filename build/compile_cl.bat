@echo off
cls
del *.obj *.ilk *.pdb *.exe

cl /nologo /Ob1 /Oi /arch:SSE2 /fp:fast /O2 /MD /GR- /EHs /W4 -I ../include -I ../deps/math_lib/include /c ../src/*.cc
cl /nologo /Ob1 /Oi /arch:SSE2 /fp:fast /O2 /MD /GR- /EHs /W4 /Fe: ../bin/main.exe *.obj ../deps/math_lib/lib/math.lib