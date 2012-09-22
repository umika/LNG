CC   = cl -c -EHsc -I.
LIB  = glut32.lib glpng.lib
LINK = link -SUBSYSTEM:console -LIBPATH:"C:\Program Files\Microsoft SDKs\Windows\v6.0A\lib" -LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\lib" -LIBPATH:. -NODEFAULTLIB:libc
OBJ  = testLNG.obj LNGframe.obj LNGclock.obj

testLNG.exe : $(OBJ)
	$(LINK) -OUT:testLNG.exe $(OBJ) $(LIB)

testLNG.obj : testLNG.cpp testLNG.h LNGframe.h LNGclock.h
	$(CC) testLNG.cpp

LNGframe.obj : LNGframe.cpp LNGframe.h LNGclock.h
	$(CC) LNGframe.cpp

LNGclock.obj : LNGclock.cpp LNGclock.h
	$(CC) LNGclock.cpp
