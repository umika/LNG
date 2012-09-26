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

TestLNG3D::TestLNG3D() : angle(0)
{
  // fps->flag_show = false;
  fps->pos = LNGcoord3f(-0.9, -0.5, 0.1);
  fps->col = LNGcolor4f(0.4, 0.2, 0.8, 0.9);
}

TestLNG3D::~TestLNG3D()
{
}

void TestLNG3D::Update(void)
{
  angle = (angle + 1) % 360;
  LNG3Dframe::Update();
}

void TestLNG3D::ChangeAngle(void)
{
  // when use rotation, must change mode in Perspective()
  glTranslatef(0.0, 0.0, -5.0);
  glRotatef(-30, 1, 0, 0);
  glRotatef(angle, 0, 1, 0);
  glRotatef(-30, 0, 0, 1);
}

void TestLNG3D::DisplayDraw(void)
{
  LNG3Dframe::DisplayDraw();
}

int main(int ac, char **av)
{
  try{
    TestLNG3D frm;
    string title = "testLNG3D";
#ifdef _DEBUG
    frm.InitFrame(&ac, av, title, LNGsize(240, 320), LNGpoint(40, 40));
#endif
    frm.InitFrame(&ac, av, title);
  }catch(LNGexception &e){
    cout << e.getstr();
  }
  return 0;
}
