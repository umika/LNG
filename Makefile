OUTPUT = testLNG
OBJS   = $(OUTPUT).obj LNGframe.obj LNGclock.obj
LIBS   = glut32.lib glpng.lib
CC     = cl
CFLAGS = -EHsc -I.
LINK   = link
LPATH0 = "C:\Program Files\Microsoft SDKs\Windows\v6.0A\lib"
LPATH1 = "C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\lib"
LPATH2 = .
LPALL  = -LIBPATH:$(LPATH0) -LIBPATH:$(LPATH1) -LIBPATH:$(LPATH2)
LFLAGS = $(LPALL) -SUBSYSTEM:console -NODEFAULTLIB:libc

$(OUTPUT).exe : $(OBJS)
	$(LINK) -OUT:$@ $(OBJS) $(LIBS) $(LFLAGS)

$(OUTPUT).obj : $*.cpp $*.h LNGframe.h LNGclock.h
	$(CC) -c $(CFLAGS) $*.cpp

LNGframe.obj : $*.cpp $*.h LNGclock.h
	$(CC) -c $(CFLAGS) $*.cpp

LNGclock.obj : $*.cpp $*.h
	$(CC) -c $(CFLAGS) $*.cpp

clean :
	del *.obj

all : clean $(OUTPUT).exe
