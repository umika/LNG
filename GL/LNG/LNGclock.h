/*
  LNGclock.h
*/

#ifndef __LNGclock_H__
#define __LNGclock_H__

#include <GL/LNG/LNGut.h>

class LNGclock {
public:
  GLuint fps, fps_clk, fps_pclk, fps_nclk, frames;
public:
  LNGclock();
  virtual ~LNGclock();
  virtual void FPS(void);
  virtual void FPSdisplay(void);
};

#endif
