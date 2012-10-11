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

TestLNG::TestLNG() : distance(5.0), box(1.5), radius(0.5),
  org(LNGcoord3f(0.0, 0.0, 0.0)), vel(LNGcoord3f(0.01, 0.02, 0.03)),
  angle(LNGcoord3f(0.0, 0.0, 0.0)), prev(LNGpoint(0, 0))
#ifdef __TEST_GLUI__
  , glui(0), view_rot(0)
#endif
{
  // clk->FPSvisible(false);
  clk->fps_pos = LNGcoord3f(-0.5, 0.8, -0.8);
  clk->fps_col = LNGcolor4f(0.2, 0.8, 0.4, 0.9);
}

TestLNG::~TestLNG()
{
}

void TestLNG::Finalize(void)
{
#ifdef __TEST_GLUI__
  if(view_rot) { delete view_rot; view_rot = 0; };
  if(glui) { delete glui; glui = 0; };
#endif
  LNG3Dframe::Finalize();
}

void TestLNG::InitGL(void)
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

#ifdef __TEST_GLUI__
  static float rotate[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
  glui = GLUI_Master.create_glui("control");
  view_rot = glui->add_rotation("Rotation", rotate);
  glui->add_button("Exit", 0, dispatcher->Quit);
#endif
}

void TestLNG::Update(void)
{
  org.x += vel.x; org.y += vel.y; org.z += vel.z;
  if((org.x + radius >= box) || (org.x - radius <= -box)) vel.x = -vel.x;
  if((org.y + radius >= box) || (org.y - radius <= -box)) vel.y = -vel.y;
  if((org.z + radius >= box) || (org.z - radius <= -box)) vel.z = -vel.z;
  angle.x += 0.15; angle.y += 0.21; angle.z += 0.1;
  if(angle.x >= 360.0) angle.x -= 360.0;
  if(angle.y >= 360.0) angle.y -= 360.0;
  if(angle.z >= 360.0) angle.z -= 360.0;
  if(angle.x < 0.0) angle.x += 360.0;
  if(angle.y < 0.0) angle.y += 360.0;
  if(angle.z < 0.0) angle.z += 360.0;
  LNG3Dframe::Update();
}

void TestLNG::ChangeAngle(void)
{
  // when use rotation, must change mode in Perspective()
  glTranslatef(0.0, 0.0, -distance);
  glRotatef(angle.x, 1, 0, 0);
  glRotatef(angle.y, 0, 1, 0);
  glRotatef(angle.z, 0, 0, 1);
}

void TestLNG::DisplayDraw(void)
{
  LNG3Dframe::DisplayDraw();

  glEnable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_LIGHTING);
  static const GLfloat mc[] = {0.2, 0.9, 0.3, 0.7};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mc);
  glTranslatef(-org.x, -org.y, -org.z);
  glutSolidSphere(radius, 20, 20);
  glTranslatef(org.x, org.y, org.z);
  glDisable(GL_LIGHTING);
  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);

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

  GLfloat p = box, q = -box;
  glDisable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  if(loader->loading){
    glColor4f(1.0, 0.0, 0.0, 0.3);
    glBegin(GL_QUADS);
    glVertex3f(q,q,q); glVertex3f(p,q,q); glVertex3f(p,p,q); glVertex3f(q,p,q);
    glEnd();
  }else{
    glColor4f(1.0, 1.0, 1.0, 0.7);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, loader->textures->at(0)->id);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(q,q,q);
    glTexCoord2f(1, 0); glVertex3f(p,q,q);
    glTexCoord2f(1, 1); glVertex3f(p,p,q);
    glTexCoord2f(0, 1); glVertex3f(q,p,q);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }
  if(loader->loading){
    glColor4f(1.0, 0.0, 0.0, 0.3);
    glBegin(GL_QUADS);
    glVertex3f(q,q,p); glVertex3f(p,q,p); glVertex3f(p,p,p); glVertex3f(q,p,p);
    glEnd();
  }else{
    glColor4f(1.0, 1.0, 1.0, 0.7);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, loader->textures->at(1)->id);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(q,q,p);
    glTexCoord2f(1, 0); glVertex3f(p,q,p);
    glTexCoord2f(1, 1); glVertex3f(p,p,p);
    glTexCoord2f(0, 1); glVertex3f(q,p,p);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }
  if(loader->loading){
    glColor4f(0.0, 1.0, 0.0, 0.3);
    glBegin(GL_QUADS);
    glVertex3f(q,q,q); glVertex3f(q,p,q); glVertex3f(q,p,p); glVertex3f(q,q,p);
    glEnd();
  }else{
    glColor4f(1.0, 1.0, 1.0, 0.7);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, loader->textures->at(2)->id);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(q,q,q);
    glTexCoord2f(1, 0); glVertex3f(q,p,q);
    glTexCoord2f(1, 1); glVertex3f(q,p,p);
    glTexCoord2f(0, 1); glVertex3f(q,q,p);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }
  if(loader->loading){
    glColor4f(0.0, 1.0, 0.0, 0.3);
    glBegin(GL_QUADS);
    glVertex3f(p,q,q); glVertex3f(p,p,q); glVertex3f(p,p,p); glVertex3f(p,q,p);
    glEnd();
  }else{
    glColor4f(1.0, 1.0, 1.0, 0.7);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, loader->textures->at(3)->id);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(p,q,q);
    glTexCoord2f(1, 0); glVertex3f(p,p,q);
    glTexCoord2f(1, 1); glVertex3f(p,p,p);
    glTexCoord2f(0, 1); glVertex3f(p,q,p);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }
  if(loader->loading){
    glColor4f(0.0, 0.0, 1.0, 0.3);
    glBegin(GL_QUADS);
    glVertex3f(q,q,q); glVertex3f(q,q,p); glVertex3f(p,q,p); glVertex3f(p,q,q);
    glEnd();
  }else{
    glColor4f(1.0, 1.0, 1.0, 0.7);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, loader->textures->at(4)->id);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(q,q,q);
    glTexCoord2f(1, 0); glVertex3f(q,q,p);
    glTexCoord2f(1, 1); glVertex3f(p,q,p);
    glTexCoord2f(0, 1); glVertex3f(p,q,q);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }
  if(loader->loading){
    glColor4f(0.0, 0.0, 1.0, 0.3);
    glBegin(GL_QUADS);
    glVertex3f(q,p,q); glVertex3f(q,p,p); glVertex3f(p,p,p); glVertex3f(p,p,q);
    glEnd();
  }else{
    glColor4f(1.0, 1.0, 1.0, 0.7);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, loader->textures->at(5)->id);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(q,p,q);
    glTexCoord2f(1, 0); glVertex3f(q,p,p);
    glTexCoord2f(1, 1); glVertex3f(p,p,p);
    glTexCoord2f(0, 1); glVertex3f(p,p,q);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }
  glDisable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
}

int main(int ac, char **av)
{
  try{
    TestLNG frm;
    string title = "testLNG";
#ifdef _DEBUG
    frm.InitFrame(&ac, av, title, LNGsize(240, 320), LNGpoint(40, 40));
#endif
    frm.InitFrame(&ac, av, title);
    frm.MainLoop();
  }catch(LNGexception &e){
    cout << e.getstr() << endl;
#if defined( __TRACE_DESTRUCTION__ ) || defined( _DEBUG )
    cout << "after LNGexception in main" << endl;
#endif
  }
#if defined( __TRACE_DESTRUCTION__ ) || defined( _DEBUG )
  cout << "now return from main" << endl;
#endif
  return 0;
}
