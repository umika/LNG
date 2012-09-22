/*
  LNGframe.cpp
*/

#include "LNGframe.h"

LNGframe::LNGframe() : fps(0)
{
  if(!fps) fps = new LNGclock();
}

LNGframe::~LNGframe()
{
  if(fps){ delete fps; fps = 0; }
}
