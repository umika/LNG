/*
  testLNG.h
*/

#ifndef __testLNG_H__
#define __testLNG_H__

#include <GL/LNG/LNG3Dframe.h>

class TestLNG : public LNG3Dframe {
protected:
  GLfloat distance, box, radius;
  LNGcoord3f org, vel, angle;
  LNGpoint prev;
public:
  TestLNG();
  virtual ~TestLNG();
  virtual void InitGL(void);
  virtual void Update(void);
  virtual void ChangeAngle(void);
  virtual void DisplayDraw(void);
};

#endif
