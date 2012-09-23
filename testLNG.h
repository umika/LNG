/*
  testLNG.h
*/

#ifndef __testLNG_H__
#define __testLNG_H__

#include <GL/LNG/LNG3Dframe.h>

class TestLNG : public LNG3Dframe {
public:
  TestLNG();
  virtual ~TestLNG();
  virtual void DisplayDraw(void);
};

#endif
