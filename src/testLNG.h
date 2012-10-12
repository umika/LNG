/*
  testLNG.h
*/

#ifndef __testLNG_H__
#define __testLNG_H__

#include <LNG/LNG3Dframe.h>

#ifdef __TEST_GLUI__
#define GLUIDLL
#include <GL/glui.h>
#endif

class TestLNG : public LNG3Dframe {
protected:
  GLfloat distance, box, radius;
  LNGcoord3f org, vel, angle;
  LNGpoint prev;
#ifdef __TEST_GLUI__
  GLUI *glui;
  GLUI_Rotation *view_rot;
#endif
public:
  TestLNG();
  virtual ~TestLNG();
  virtual void Finalize(void);
  virtual void LoadTextures(void);
  virtual void InitGL(void);
  virtual void Update(void);
  virtual void ChangeAngle(void);
  virtual void DisplayDraw(void);
};

#endif
