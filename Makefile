OUTPUT = testLNG
HEADS  = LNGframe.h LNGclock.h LNGut.h LNGtypes.h
OBJS   = LNGframe.obj LNGclock.obj LNGut.obj
LIBS   = glut32.lib glpng.lib
CC     = cl
CFLAGS = -EHsc -I.
SUBSYS = -SUBSYSTEM:console
NOLIB  = -NODEFAULTLIB:libc
#LINK   = link
LPATH0 = -LIBPATH:.
#LPATH1 = -LIBPATH:"C:\Program Files\Microsoft SDKs\Windows\v6.0A\lib"
#LPATH2 = -LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\lib"
#LPALL  = $(LPATH0) $(LPATH1) $(LPATH2)
#LFLAGS = $(LPALL) $(SUBSYS) $(NOLIB)
LINK   = cl
LFLAGS = -link $(LPATH0) $(SUBSYS) $(NOLIB)

$(OUTPUT).exe : $*.obj LNG3Dframe.obj $(OBJS)
	$(LINK) $*.obj LNG3Dframe.obj $(OBJS) $(LIBS) $(LFLAGS) -OUT:$@

$(OUTPUT).obj : $*.cpp $*.h LNG3Dframe.h $(HEADS)
	$(CC) -c $(CFLAGS) $*.cpp

testLNG3D.exe : $*.obj LNG3Dframe.obj $(OBJS)
	$(LINK) $*.obj LNG3Dframe.obj $(OBJS) $(LIBS) $(LFLAGS) -OUT:$@

testLNG3D.obj : $*.cpp $*.h LNG3Dframe.h $(HEADS)
	$(CC) -c $(CFLAGS) $*.cpp

LNG3Dframe.obj : $*.cpp $*.h $(HEADS)
	$(CC) -c $(CFLAGS) $*.cpp

testLNG2D.exe : $*.obj LNG2Dframe.obj $(OBJS)
	$(LINK) $*.obj LNG2Dframe.obj $(OBJS) $(LIBS) $(LFLAGS) -OUT:$@

testLNG2D.obj : $*.cpp $*.h LNG2Dframe.h $(HEADS)
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

all : clean $(OUTPUT).exe testLNG3D.exe testLNG2D.exe
