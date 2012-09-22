/*
  LNGframe.h
*/

#ifndef __LNGframe_H__
#define __LNGframe_H__

#include <GL/glut.h>
#include "LNGclock.h"

class LNGframe {
protected:
  LNGclock *fps;
public:
  LNGframe();
  virtual ~LNGframe();
};

#endif
