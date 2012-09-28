OUTPUT = glLNG.lib
LDIR   = libs/
HDIR   = GL/LNG/
HEADS0 = $(HDIR)LNGtexture.h $(HDIR)LNGclock.h $(HDIR)LNGut.h $(HDIR)LNGtypes.h
HEADS1 = $(HDIR)LNGframe.h
HEADS  = $(HEADS1) $(HEADS0)
TDIR   = src/
SDIR   = src/LNG/
ODIR   = objs/
OBJS0  = $(ODIR)LNGtexture.obj $(ODIR)LNGclock.obj $(ODIR)LNGut.obj
OBJS1  = $(ODIR)LNGframe.obj
OBJS   = $(ODIR)LNG3Dframe.obj $(ODIR)LNG2Dframe.obj $(OBJS1) $(OBJS0)
LIBS   = $(OUTPUT) glpng.lib glui32dll.lib glut32.lib
CC     = cl
CPPTR0 = $(TRACE_CONSTRUCTION) $(TRACE_DESTRUCTION)
CPPTR1 = $(TRACE_CREATION) $(TRACE_FINALIZATION)
CFLAGS = $(CPPTR1) $(CPPTR0) -nologo -EHsc -I.
SUBSYS = -SUBSYSTEM:console
NOLIB  = -NODEFAULTLIB:libc
LOPT   = -nologo -link
LINK   = cl
#LINK   = link
LPATH0 = -LIBPATH:$(LDIR)
#LPATH1 = -LIBPATH:"C:\Program Files\Microsoft SDKs\Windows\v6.0A\lib"
#LPATH2 = -LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\lib"
LPALL  = $(LPATH2) $(LPATH1) $(LPATH0)
LFLAGS = -NOLOGO $(LPALL) $(SUBSYS) $(NOLIB)
LIBEXE = lib

$(LDIR)$(OUTPUT) : $(OBJS)
	$(LIBEXE) $(OBJS) $(LFLAGS) -OUT:$(LDIR)$(@F)

testLNG.exe : $(ODIR)$(*B).obj $(LDIR)$(OUTPUT)
	$(LINK) $(ODIR)$(*B).obj $(LIBS) $(LOPT) $(LFLAGS) -OUT:$(@F)

$(ODIR)testLNG.obj : $(TDIR)$(*B).cpp $(TDIR)$(*B).h $(HDIR)LNG3Dframe.h $(HEADS)
	$(CC) -c $(CFLAGS) $(TDIR)$(*B).cpp -Fo$(ODIR)$(@F)

testLNGsphere.exe : $(ODIR)$(*B).obj $(LDIR)$(OUTPUT)
	$(LINK) $(ODIR)$(*B).obj $(LIBS) $(LOPT) $(LFLAGS) -OUT:$(@F)

$(ODIR)testLNGsphere.obj : $(TDIR)$(*B).cpp $(TDIR)$(*B).h $(HDIR)LNG3Dframe.h $(HEADS)
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

$(ODIR)LNGtexture.obj : $(SDIR)$(*B).cpp $(HDIR)$(*B).h $(HDIR)LNGut.h $(HDIR)LNGtypes.h
	$(CC) -c $(CFLAGS) $(SDIR)$(*B).cpp -Fo$(ODIR)$(@F)

$(ODIR)LNGclock.obj : $(SDIR)$(*B).cpp $(HDIR)$(*B).h $(HDIR)LNGut.h $(HDIR)LNGtypes.h
	$(CC) -c $(CFLAGS) $(SDIR)$(*B).cpp -Fo$(ODIR)$(@F)

$(ODIR)LNGut.obj : $(SDIR)$(*B).cpp $(HDIR)$(*B).h $(HDIR)LNGtypes.h
	$(CC) -c $(CFLAGS) $(SDIR)$(*B).cpp -Fo$(ODIR)$(@F)

clean :
	del objs\*.obj

all : clean $(LDIR)$(OUTPUT) testLNG2D.exe testLNG3D.exe testLNGsphere.exe testLNG.exe
