/*
  testLNG.h
*/

#ifndef __testLNG_H__
#define __testLNG_H__

#include "LNGframe.h"

class TestLNG : public LNGframe {
public:
  TestLNG();
  virtual ~TestLNG();
  virtual void ChangeAngle(void);
  virtual void DisplayDraw(void);
  virtual void Perspective(int w, int h);
};

#endif
