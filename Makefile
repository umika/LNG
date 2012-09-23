OUTPUT = glLNG.lib
HEADS  = LNGframe.h LNGclock.h LNGut.h LNGtypes.h
OBJS   = LNG3Dframe.obj LNG2Dframe.obj LNGframe.obj LNGclock.obj LNGut.obj
LIBS   = $(OUTPUT) glpng.lib glut32.lib
CC     = cl
CFLAGS = -EHsc -I.
SUBSYS = -SUBSYSTEM:console
NOLIB  = -NODEFAULTLIB:libc
LOPT   = -link
LINK   = cl
#LINK   = link
LPATH0 = -LIBPATH:.
LPATH1 = -LIBPATH:"C:\Program Files\Microsoft SDKs\Windows\v6.0A\lib"
LPATH2 = -LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\lib"
LPALL  = $(LPATH0) $(LPATH1) $(LPATH2)
LFLAGS = $(LPALL) $(SUBSYS) $(NOLIB)
LIB    = lib

$(OUTPUT) : $(OBJS)
	$(LIB) $(OBJS) $(LFLAGS) -OUT:$@

testLNG.exe : $*.obj $(OUTPUT)
	$(LINK) $*.obj $(LIBS) $(LOPT) $(LFLAGS) -OUT:$@

testLNG.obj : $*.cpp $*.h LNG3Dframe.h $(HEADS)
	$(CC) -c $(CFLAGS) $*.cpp

testLNG3D.exe : $*.obj $(OUTPUT)
	$(LINK) $*.obj $(LIBS) $(LOPT) $(LFLAGS) -OUT:$@

testLNG3D.obj : $*.cpp $*.h LNG3Dframe.h $(HEADS)
	$(CC) -c $(CFLAGS) $*.cpp

testLNG2D.exe : $*.obj $(OUTPUT)
	$(LINK) $*.obj $(LIBS) $(LOPT) $(LFLAGS) -OUT:$@

testLNG2D.obj : $*.cpp $*.h LNG2Dframe.h $(HEADS)
	$(CC) -c $(CFLAGS) $*.cpp

LNG3Dframe.obj : $*.cpp $*.h $(HEADS)
	$(CC) -c $(CFLAGS) $*.cpp

LNG2Dframe.obj : $*.cpp $*.h $(HEADS)
	$(CC) -c $(CFLAGS) $*.cpp

LNGframe.obj : $*.cpp $*.h LNGclock.h LNGut.h LNGtypes.h
	$(CC) -c $(CFLAGS) $*.cpp

LNGclock.obj : $*.cpp $*.h LNGut.h LNGtypes.h
	$(CC) -c $(CFLAGS) $*.cpp

LNGut.obj : $*.cpp $*.h LNGtypes.h
	$(CC) -c $(CFLAGS) $*.cpp

clean :
	del *.obj

all : clean $(OUTPUT) testLNG2D.exe testLNG3D.exe testLNG.exe
