/*
  LNGclock.h
*/

#ifndef __LNGclock_H__
#define __LNGclock_H__

#include <GL/LNG/LNGut.h>

class LNGclock {
protected:
  GLuint fpsclk;
public:
  LNGclock();
  virtual ~LNGclock();
  void FPS(void);
};

#endif
