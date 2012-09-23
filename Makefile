OUTPUT = glLNG.lib
HDIR   = GL/LNG/
HEADS  = $(HDIR)LNGframe.h $(HDIR)LNGclock.h $(HDIR)LNGut.h $(HDIR)LNGtypes.h
SDIR   = src/LNG/
OBJS   = LNG3Dframe.obj LNG2Dframe.obj LNGframe.obj LNGclock.obj LNGut.obj
TDIR   = src/
LIBS   = $(OUTPUT) glpng.lib glut32.lib
CC     = cl
CFLAGS = -nologo -EHsc -I.
SUBSYS = -SUBSYSTEM:console
NOLIB  = -NODEFAULTLIB:libc
LOPT   = -nologo -link
LINK   = cl
#LINK   = link
LPATH0 = -LIBPATH:.
LPATH1 = -LIBPATH:"C:\Program Files\Microsoft SDKs\Windows\v6.0A\lib"
LPATH2 = -LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\lib"
LPALL  = $(LPATH0) $(LPATH1) $(LPATH2)
LFLAGS = -NOLOGO $(LPALL) $(SUBSYS) $(NOLIB)
LIB    = lib

$(OUTPUT) : $(OBJS)
	$(LIB) $(OBJS) $(LFLAGS) -OUT:$@

testLNG.exe : $*.obj $(OUTPUT)
	$(LINK) $*.obj $(LIBS) $(LOPT) $(LFLAGS) -OUT:$@

testLNG.obj : $*.cpp $*.h $(HDIR)LNG3Dframe.h $(HEADS)
	$(CC) -c $(CFLAGS) $*.cpp

testLNG3D.exe : $*.obj $(OUTPUT)
	$(LINK) $*.obj $(LIBS) $(LOPT) $(LFLAGS) -OUT:$@

testLNG3D.obj : $*.cpp $*.h $(HDIR)LNG3Dframe.h $(HEADS)
	$(CC) -c $(CFLAGS) $*.cpp

testLNG2D.exe : $*.obj $(OUTPUT)
	$(LINK) $*.obj $(LIBS) $(LOPT) $(LFLAGS) -OUT:$@

testLNG2D.obj : $*.cpp $*.h $(HDIR)LNG2Dframe.h $(HEADS)
	$(CC) -c $(CFLAGS) $*.cpp

LNG3Dframe.obj : $(SDIR)$*.cpp $(HDIR)$*.h $(HEADS)
	$(CC) -c $(CFLAGS) $(SDIR)$*.cpp

LNG2Dframe.obj : $(SDIR)$*.cpp $(HDIR)$*.h $(HEADS)
	$(CC) -c $(CFLAGS) $(SDIR)$*.cpp

LNGframe.obj : $(SDIR)$*.cpp $(HDIR)$*.h $(HEADS)
	$(CC) -c $(CFLAGS) $(SDIR)$*.cpp

LNGclock.obj : $(SDIR)$*.cpp $(HDIR)$*.h $(HDIR)LNGut.h $(HDIR)LNGtypes.h
	$(CC) -c $(CFLAGS) $(SDIR)$*.cpp

LNGut.obj : $(SDIR)$*.cpp $(HDIR)$*.h $(HDIR)LNGtypes.h
	$(CC) -c $(CFLAGS) $(SDIR)$*.cpp

clean :
	del *.obj

all : clean $(OUTPUT) testLNG2D.exe testLNG3D.exe testLNG.exe
