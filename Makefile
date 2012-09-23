OUTPUT = glLNG.lib
LDIR   = libs/
HDIR   = GL/LNG/
HEADS  = $(HDIR)LNGframe.h $(HDIR)LNGclock.h $(HDIR)LNGut.h $(HDIR)LNGtypes.h
TDIR   = src/
SDIR   = src/LNG/
ODIR   = objs/
OBJS0  = $(ODIR)LNGframe.obj $(ODIR)LNGclock.obj $(ODIR)LNGut.obj
OBJS   = $(ODIR)LNG3Dframe.obj $(ODIR)LNG2Dframe.obj $(OBJS0)
LIBS   = $(OUTPUT) glpng.lib glut32.lib
CC     = cl
CFLAGS = -nologo -EHsc -I.
SUBSYS = -SUBSYSTEM:console
NOLIB  = -NODEFAULTLIB:libc
LOPT   = -nologo -link
LINK   = cl
#LINK   = link
LPATH0 = -LIBPATH:$(LDIR)
LPATH1 = -LIBPATH:"C:\Program Files\Microsoft SDKs\Windows\v6.0A\lib"
LPATH2 = -LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\lib"
LPALL  = $(LPATH0) $(LPATH1) $(LPATH2)
LFLAGS = -NOLOGO $(LPALL) $(SUBSYS) $(NOLIB)
LIB    = lib

$(LDIR)$(OUTPUT) : $(OBJS)
	$(LIB) $(OBJS) $(LFLAGS) -OUT:$(LDIR)$(@F)

testLNG.exe : $(ODIR)$(*B).obj $(LDIR)$(OUTPUT)
	$(LINK) $(ODIR)$(*B).obj $(LIBS) $(LOPT) $(LFLAGS) -OUT:$(@F)

$(ODIR)testLNG.obj : $(TDIR)$(*B).cpp $(TDIR)$(*B).h $(HDIR)LNG3Dframe.h $(HEADS)
	$(CC) -c $(CFLAGS) $(TDIR)$(*B).cpp -Fo$(ODIR)$(@F)

testLNG3D.exe : $(ODIR)$(*B).obj $(LDIR)$(OUTPUT)
	$(LINK) $(ODIR)$(*B).obj $(LIBS) $(LOPT) $(LFLAGS) -OUT:$(@F)

$(ODIR)testLNG3D.obj : $(TDIR)$(*B).cpp $(TDIR)$(*B).h $(HDIR)LNG3Dframe.h $(HEADS)
	$(CC) -c $(CFLAGS) $(TDIR)$(*B).cpp -Fo$(ODIR)$(@F)

testLNG2D.exe : $(ODIR)$(*B).obj $(LDIR)$(OUTPUT)
	$(LINK) $(ODIR)$(*B).obj $(LIBS) $(LOPT) $(LFLAGS) -OUT:$(@F)

$(ODIR)testLNG2D.obj : $(TDIR)$(*B).cpp $(TDIR)$(*B).h $(HDIR)LNG2Dframe.h $(HEADS)
	$(CC) -c $(CFLAGS) $(TDIR)$(*B).cpp -Fo$(ODIR)$(@F)

$(ODIR)LNG3Dframe.obj : $(SDIR)$(*B).cpp $(HDIR)$(*B).h $(HEADS)
	$(CC) -c $(CFLAGS) $(SDIR)$(*B).cpp -Fo$(ODIR)$(@F)

$(ODIR)LNG2Dframe.obj : $(SDIR)$(*B).cpp $(HDIR)$(*B).h $(HEADS)
	$(CC) -c $(CFLAGS) $(SDIR)$(*B).cpp -Fo$(ODIR)$(@F)

$(ODIR)LNGframe.obj : $(SDIR)$(*B).cpp $(HDIR)$(*B).h $(HEADS)
	$(CC) -c $(CFLAGS) $(SDIR)$(*B).cpp -Fo$(ODIR)$(@F)

$(ODIR)LNGclock.obj : $(SDIR)$(*B).cpp $(HDIR)$(*B).h $(HDIR)LNGut.h $(HDIR)LNGtypes.h
	$(CC) -c $(CFLAGS) $(SDIR)$(*B).cpp -Fo$(ODIR)$(@F)

$(ODIR)LNGut.obj : $(SDIR)$(*B).cpp $(HDIR)$(*B).h $(HDIR)LNGtypes.h
	$(CC) -c $(CFLAGS) $(SDIR)$(*B).cpp -Fo$(ODIR)$(@F)

clean :
	del objs\*.obj

all : clean $(LDIR)$(OUTPUT) testLNG2D.exe testLNG3D.exe testLNG.exe
