/*
  LNG2Dframe.h
*/

#ifndef __LNG2Dframe_H__
#define __LNG2Dframe_H__

#include <LNG/LNGframe.h>

class LNG2Dframe : public LNGframe {
public:
  LNG2Dframe() {}
  virtual ~LNG2Dframe() {}
  virtual void Ortho(
    float x0, float x1, float y0, float y1, float z0, float z1);
};

#endif
