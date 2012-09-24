/*
  testLNG2D.h
*/

#ifndef __testLNG2D_H__
#define __testLNG2D_H__

#include <GL/LNG/LNG2Dframe.h>

class TestLNG2D : public LNG2Dframe {
public:
  TestLNG2D();
  virtual ~TestLNG2D();
  virtual void DisplayDraw(void);
};

#endif
