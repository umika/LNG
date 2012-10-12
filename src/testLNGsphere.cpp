/*
  testLNGsphere.cpp

  > cl testLNGsphere.cpp LNG3Dframe.cpp \
    LNGframe.cpp LNGclock.cpp glut32.lib glpng.lib -EHsc -I. \
    -link -LIBPATH:. -SUBSYSTEM:console -NODEFAULTLIB:libc

  -EHsc destroy local objects on catch any exception
  -NODEFAULTLIB:libc recent VC++ links 'libcmt.lib' instead of 'libc.lib'
  'GL/glut.h' 'glut32.lib' 'glut32.dll' from glut-3.7.6-bin.zip
  'GL/glpng.h' 'glpng.lib' from http://openports.se/graphics/glpng
*/

#include "testLNGsphere.h"

using namespace std;

TestLNGsphere::TestLNGsphere() : distance(5.0),
  angle(LNGcoord3f(0.0, 0.0, 0.0)), prev(LNGpoint(0, 0))
{
  // clk->FPSvisible(false);
  clk->fps_pos = LNGcoord3f(-0.5, 0.8, -0.8);
  clk->fps_col = LNGcolor4f(0.2, 0.8, 0.4, 0.9);
}

TestLNGsphere::~TestLNGsphere()
{
}

void TestLNGsphere::InitGL(void)
{
  LNG3Dframe::InitGL();
  static const GLfloat l0d[] = {0.8, 0.8, 0.8, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, l0d);
  static const GLfloat l0a[] = {0.2, 0.2, 0.2, 1.0};
  glLightfv(GL_LIGHT0, GL_AMBIENT, l0a);
  static const GLfloat l0p[] = {1.0, 1.0, 1.0, 0.0};
  glLightfv(GL_LIGHT0, GL_POSITION, l0p);
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
  glClearDepth(1.0);
}

void TestLNGsphere::Update(void)
{
  angle.x = angle.x + 1.5;
  angle.y = angle.y + 2.1;
  angle.z = angle.z + 0.1;
  if(angle.x >= 360.0) angle.x -= 360.0;
  if(angle.y >= 360.0) angle.y -= 360.0;
  if(angle.z >= 360.0) angle.z -= 360.0;
  if(angle.x < 0.0) angle.x += 360.0;
  if(angle.y < 0.0) angle.y += 360.0;
  if(angle.z < 0.0) angle.z += 360.0;
  LNG3Dframe::Update();
}

void TestLNGsphere::ChangeAngle(void)
{
  // when use rotation, must change mode in Perspective()
  glTranslatef(0.0, 0.0, -distance);
  glRotatef(angle.x, 1, 0, 0);
  glRotatef(angle.y, 0, 1, 0);
  glRotatef(angle.z, 0, 0, 1);
}

void TestLNGsphere::DisplayDraw(void)
{
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  static const GLfloat mc[] = {0.5, 0.5, 1.0, 1.0};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mc);
  glutSolidSphere(0.5, 20, 20);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);

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

  glDisable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glColor4f(1.0, 0.0, 0.0, 0.7);
  glBegin(GL_QUADS);
  glVertex3f(0,0,0); glVertex3f(1,0,0); glVertex3f(1,1,0); glVertex3f(0,1,0);
  glEnd();
  glColor4f(0.0, 1.0, 0.0, 0.7);
  glBegin(GL_QUADS);
  glVertex3f(0,0,0); glVertex3f(0,1,0); glVertex3f(0,1,1); glVertex3f(0,0,1);
  glEnd();
  glColor4f(0.0, 0.0, 1.0, 0.7);
  glBegin(GL_QUADS);
  glVertex3f(0,0,0); glVertex3f(0,0,1); glVertex3f(1,0,1); glVertex3f(1,0,0);
  glEnd();
  glDisable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
}

int main(int ac, char **av)
{
  try{
    TestLNGsphere frm;
    string title = "testLNGsphere";
#ifdef _DEBUG
    frm.InitFrame(&ac, av, title, LNGsize(240, 320), LNGpoint(40, 40));
#endif
    frm.InitFrame(&ac, av, title);
    frm.MainLoop();
  }catch(LNGexception &e){
    cout << e.getstr() << endl;
  }
  return 0;
}
