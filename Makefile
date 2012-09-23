OUTPUT = testLNG
OBJS   = $(OUTPUT).obj LNGframe.obj LNGclock.obj
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

$(OUTPUT).exe : $(OBJS)
	$(LINK) $(OBJS) $(LIBS) $(LFLAGS) -OUT:$@

$(OUTPUT).obj : $*.cpp $*.h LNGframe.h LNGclock.h
	$(CC) -c $(CFLAGS) $*.cpp

LNGframe.obj : $*.cpp $*.h LNGclock.h
	$(CC) -c $(CFLAGS) $*.cpp

LNGclock.obj : $*.cpp $*.h
	$(CC) -c $(CFLAGS) $*.cpp

clean :
	del *.obj

all : clean $(OUTPUT).exe
