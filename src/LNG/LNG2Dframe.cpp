/*
  LNG2Dframe.cpp
*/

#include <LNG/LNG2Dframe.h>

using namespace std;

void LNG2Dframe::Ortho(
  float x0, float x1, float y0, float y1, float z0, float z1)
{
  glOrtho(x0, x1, y0, y1, z0, z1); // use without ChangeAngle()
}
