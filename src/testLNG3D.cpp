/*
  testLNG3D.cpp

  > cl testLNG3D.cpp LNG3Dframe.cpp \
    LNGframe.cpp LNGclock.cpp glut32.lib glpng.lib -EHsc -I. \
    -link -LIBPATH:. -SUBSYSTEM:console -NODEFAULTLIB:libc

  -EHsc destroy local objects on catch any exception
  -NODEFAULTLIB:libc recent VC++ links 'libcmt.lib' instead of 'libc.lib'
  'GL/glut.h' 'glut32.lib' 'glut32.dll' from glut-3.7.6-bin.zip
  'GL/glpng.h' 'glpng.lib' from http://openports.se/graphics/glpng
*/

#include "testLNG3D.h"

using namespace std;

void TestLNG3D::DisplayDraw(void)
{
  LNG3Dframe::DisplayDraw();
}

int main(int ac, char **av)
{
  TestLNG3D frm;
  string title = "testLNG3D";
#ifdef _DEBUG
  frm.InitFrame(&ac, av, title, LNGsize(240, 320), LNGpoint(40, 40));
#endif
  frm.InitFrame(&ac, av, title);
  return 0;
}
