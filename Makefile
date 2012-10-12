OUTPUT = liblng.lib
LDIR   = lib/
HDIR   = include/LNG/
HEADS0 = $(HDIR)LNGclock.h $(HDIR)LNGut.h $(HDIR)LNGtypes.h
HEADS1 = $(HDIR)LNGtexture.h $(HDIR)LNGpng.h
HEADS2 = $(HDIR)LNGchar_texture.h $(HDIR)LNGcameleon_texture.h
HEADS3 = $(HDIR)LNGframe.h
HEADS  = $(HEADS3) $(HEADS2) $(HEADS1) $(HEADS0)
TDIR   = src/
SDIR   = src/LNG/
ODIR   = obj/
OBJS0  = $(ODIR)LNGclock.obj $(ODIR)LNGut.obj
OBJS1  = $(ODIR)LNGtexture.obj $(ODIR)LNGpng.obj
OBJS2  = $(ODIR)LNGchar_texture.obj $(ODIR)LNGcameleon_texture.obj
OBJS3  = $(ODIR)LNG3Dframe.obj $(ODIR)LNG2Dframe.obj $(ODIR)LNGframe.obj
OBJS   = $(OBJS3) $(OBJS2) $(OBJS1) $(OBJS0)
LIBS   = $(OUTPUT) zlib1.lib libpng15.lib glui32dll.lib glut32.lib
CC     = cl
CPPTR0 = $(TRACE_CONSTRUCTION) $(TRACE_DESTRUCTION)
CPPTR1 = $(TRACE_CREATION) $(TRACE_FINALIZATION)
CPPDEF = $(TEST_GLUI)
CFLAGS = $(CPPDEF) $(CPPTR1) $(CPPTR0) -nologo -EHsc -Iinclude
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

$(ODIR)LNGchar_texture.obj : $(SDIR)$(*B).cpp $(HDIR)$(*B).h $(HDIR)LNGtexture.h $(HDIR)LNGpng.h $(HDIR)LNGut.h $(HDIR)LNGtypes.h
	$(CC) -c $(CFLAGS) $(SDIR)$(*B).cpp -Fo$(ODIR)$(@F)

$(ODIR)LNGcameleon_texture.obj : $(SDIR)$(*B).cpp $(HDIR)$(*B).h $(HDIR)LNGtexture.h $(HDIR)LNGpng.h $(HDIR)LNGut.h $(HDIR)LNGtypes.h
	$(CC) -c $(CFLAGS) $(SDIR)$(*B).cpp -Fo$(ODIR)$(@F)

$(ODIR)LNGtexture.obj : $(SDIR)$(*B).cpp $(HDIR)$(*B).h $(HDIR)LNGpng.h $(HDIR)LNGut.h $(HDIR)LNGtypes.h
	$(CC) -c $(CFLAGS) $(SDIR)$(*B).cpp -Fo$(ODIR)$(@F)

$(ODIR)LNGpng.obj : $(SDIR)$(*B).cpp $(HDIR)$(*B).h $(HDIR)LNGut.h $(HDIR)LNGtypes.h
	$(CC) -c $(CFLAGS) $(SDIR)$(*B).cpp -Fo$(ODIR)$(@F)

$(ODIR)LNGclock.obj : $(SDIR)$(*B).cpp $(HDIR)$(*B).h $(HDIR)LNGut.h $(HDIR)LNGtypes.h
	$(CC) -c $(CFLAGS) $(SDIR)$(*B).cpp -Fo$(ODIR)$(@F)

$(ODIR)LNGut.obj : $(SDIR)$(*B).cpp $(HDIR)$(*B).h $(HDIR)LNGtypes.h
	$(CC) -c $(CFLAGS) $(SDIR)$(*B).cpp -Fo$(ODIR)$(@F)

pngreview.exe : $(ODIR)$(*B).obj
	$(LINK) $(ODIR)$(*B).obj zlib1.lib $(LOPT) $(LFLAGS) -OUT:$(@F)

$(ODIR)pngreview.obj : $(TDIR)$(*B).cpp
	$(CC) -c $(CFLAGS) $(TDIR)$(*B).cpp -Fo$(ODIR)$(@F)

clean :
	del obj\*.obj

all : clean pngreview.exe $(LDIR)$(OUTPUT) testLNG2D.exe testLNG3D.exe testLNGsphere.exe testLNG.exe
