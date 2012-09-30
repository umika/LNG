/*
  LNGclock.cpp
*/

#include <GL/LNG/LNGclock.h>

using namespace std;

LNGcoord3f const LNGclock::default_pos(0.0, 0.0, 0.0);
LNGcolor4f const LNGclock::default_col(1.0, 1.0, 1.0, 1.0);

LNGclock::LNGclock(GLuint a_fps_desired) :
  fps_pos(default_pos), fps_col(default_col),
  fps_desired(a_fps_desired), fps_visible(true),
  fps(0), fps_clk(0), fps_pclk(0), fps_nclk(0), frames(0)
{
}

LNGclock::~LNGclock()
{
}

void LNGclock::FPS(void)
{
  ++frames;
  fps_clk = glutGet(GLUT_ELAPSED_TIME); // has limited resolution
  if(fps_clk < fps_nclk) return;
  fps = frames;
  fps_pclk = fps_clk;
  fps_nclk = fps_clk + 1000;
  frames = 0;
}

void LNGclock::FPSdisplay(void)
{
  if(!FPSvisible()) return;
  ostringstream oss;
  oss << fps << " FPS";
  string &s = oss.str();
  glDisable(GL_TEXTURE_2D);
  glColor4f(fps_col.r, fps_col.g, fps_col.b, fps_col.a);
  // glWindowPos2f(0.0, 0.0);
  // glRasterPos2f(0.0, 0.0);
  glRasterPos3f(fps_pos.x, fps_pos.y, fps_pos.z);
  for(string::iterator it = s.begin(); it != s.end(); ++it)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *it);
  glEnable(GL_TEXTURE_2D);
#ifdef _DEBUG
  cout << s << endl;
#endif
}
