/*
  LNGclock.h
*/

#ifndef __LNGclock_H__
#define __LNGclock_H__

#include <GL/LNG/LNGut.h>

class LNGclock {
public:
  bool flag_show;
  LNGcoord3f pos;
  LNGcolor4f col;
  static LNGcoord3f const default_pos;
  static LNGcolor4f const default_col;
protected:
  GLuint const fps_desired;
  GLuint fps, fps_clk, fps_pclk, fps_nclk, frames;
public:
  LNGclock(GLuint a_fps_desired);
  virtual ~LNGclock();
  GLuint desired(void) {return fps_desired;}
  virtual void FPS(void);
  virtual void FPSdisplay(void);
};

#endif
