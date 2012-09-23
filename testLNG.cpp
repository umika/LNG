/*
  testLNG.cpp

  > cl testLNG.cpp LNGframe.cpp LNGclock.cpp glut32.lib glpng.lib -EHsc -I. \
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

void TestLNG::ChangeAngle(void)
{
  // when use rotation, must change mode in Perspective()
  glTranslatef(0.0, 0.0, -5.0);
  glRotatef(-10, 1, 0, 0);
  glRotatef(-10, 0, 1, 0);
  glRotatef(-10, 0, 0, 1);
}

void TestLNG::DisplayDraw(void)
{
  glBlendFunc(GL_SRC_COLOR, GL_SRC_ALPHA);
  glEnable(GL_BLEND);
  glColor4f(0.0, 1.0, 0.0, 3.0);
  glBegin(GL_TRIANGLES);
    glVertex3f(-0.25, -0.25, -0.25);
    glVertex3f( 0.25, -0.25, -0.25);
    glVertex3f(  0.0,  0.25, -0.25);
  glEnd();
  glDisable(GL_BLEND);
  LNGframe::DisplayDraw();
}

void TestLNG::Perspective(int w, int h)
{
//  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // use without ChangeAngle()
  gluPerspective(45, (float)w / (float)h, 1, 1000); // use with ChangeAngle()
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
