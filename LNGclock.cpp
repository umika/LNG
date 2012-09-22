/*
  LNGclock.cpp
*/

#include "LNGclock.h"

LNGclock::LNGclock() : fpsclk(0)
{
  // nothing
}

LNGclock::~LNGclock()
{
  // nothing
}

void LNGclock::FPS(void)
{
  fpsclk = glutGet(GLUT_ELAPSED_TIME); // has limited resolution
}
