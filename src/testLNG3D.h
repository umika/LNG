/*
  testLNG3D.h
*/

#ifndef __testLNG3D_H__
#define __testLNG3D_H__

#include <GL/LNG/LNG3Dframe.h>

class TestLNG3D : public LNG3Dframe {
public:
  TestLNG3D() {};
  virtual ~TestLNG3D() {};
  virtual void DisplayDraw(void);
};

#endif
