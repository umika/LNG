/*
  LNG3Dframe.h
*/

#ifndef __LNG3Dframe_H__
#define __LNG3Dframe_H__

#include "LNGframe.h"

class LNG3Dframe : public LNGframe {
public:
  LNG3Dframe() {};
  virtual ~LNG3Dframe() {};
  virtual void ChangeAngle(void);
  virtual void Perspective(int w, int h);
};

#endif
