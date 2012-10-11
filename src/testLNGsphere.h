/*
  testLNGsphere.h
*/

#ifndef __testLNGsphere_H__
#define __testLNGsphere_H__

#include <LNG/LNG3Dframe.h>

class TestLNGsphere : public LNG3Dframe {
protected:
  GLfloat distance;
  LNGcoord3f angle;
  LNGpoint prev;
public:
  TestLNGsphere();
  virtual ~TestLNGsphere();
  virtual void InitClk(GLuint fps_desired=LNGframe::default_fps);
  virtual void InitGL(void);
  virtual void Update(void);
  virtual void ChangeAngle(void);
  virtual void DisplayDraw(void);
};

#endif
