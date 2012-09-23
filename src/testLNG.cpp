/*
  testLNG.cpp

  > cl testLNG.cpp LNG3Dframe.cpp \
    LNGframe.cpp LNGclock.cpp glut32.lib glpng.lib -EHsc -I. \
    -link -LIBPATH:. -SUBSYSTEM:console -NODEFAULTLIB:libc

  -EHsc destroy local objects on catch any exception
  -NODEFAULTLIB:libc recent VC++ links 'libcmt.lib' instead of 'libc.lib'
  'GL/glut.h' 'glut32.lib' 'glut32.dll' from glut-3.7.6-bin.zip
  'GL/glpng.h' 'glpng.lib' from http://openports.se/graphics/glpng
*/

#include "testLNG.h"

using namespace std;

TestLNG::TestLNG()
{
}

TestLNG::~TestLNG()
{
}

void TestLNG::DisplayDraw(void)
{
  LNG3Dframe::DisplayDraw();
  glDisable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glColor4f(1.0, 1.0, 0.0, 0.3);
  glBegin(GL_TRIANGLES);
    glVertex3f(-1.0, -1.0, -0.2);
    glVertex3f( 0.5, -1.0, -0.2);
    glVertex3f( 0.6,  1.0, -0.2);
  glEnd();
  glDisable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
}

int main(int ac, char **av)
{
  TestLNG frm;
  string title = "testLNG";
#ifdef _DEBUG
  frm.InitFrame(&ac, av, title, LNGsize(240, 320), LNGpoint(40, 40));
#endif
  frm.InitFrame(&ac, av, title);
  return 0;
}
