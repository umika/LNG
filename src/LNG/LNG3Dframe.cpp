/*
  LNG3Dframe.cpp
*/

#include <LNG/LNG3Dframe.h>

using namespace std;

void LNG3Dframe::ChangeAngle(void)
{
  // when use rotation, must change mode in Perspective()
  glTranslatef(0.0, 0.0, -5.0);
  glRotatef(-30, 1, 0, 0);
  glRotatef(-30, 0, 1, 0);
  glRotatef(-30, 0, 0, 1);
}

void LNG3Dframe::Perspective(int w, int h)
{
  gluPerspective(45, (float)w / (float)h, 1, 1000); // use with ChangeAngle()
}
