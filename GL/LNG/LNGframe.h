/*
  LNGframe.h
*/

#ifndef __LNGframe_H__
#define __LNGframe_H__

#include <GL/LNG/LNGut.h>
#include <GL/LNG/LNGclock.h>

class LNGframe;
class LNGdispatcher;

class LNGframe {
public:
  static LNGsize const default_size;
  static LNGpoint const default_pos;
protected:
  LNGdispatcher *dispatcher;
  LNGclock *fps;
public:
  LNGframe();
  virtual ~LNGframe();
  virtual void InitFrame(int *ac, char **av, std::string &title,
    LNGsize size=default_size, LNGpoint pos=default_pos,
    GLuint mode=GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  virtual void LoadTextures(void) {};
  virtual void InitGL(void);
  virtual void Timer(int dt);
  virtual void Idle(void);
  virtual void Update(void);
  virtual void ChangeAngle(void) {};
  virtual void ChangeView(void);
  virtual void DisplayBefore(void);
  virtual void DisplayDraw(void);
  virtual void DisplayAfter(void);
  virtual void Display(void);
  virtual void Ortho(
    float x0, float x1, float y0, float y1, float z0, float z1) {};
  virtual void Perspective(int w, int h) {};
  virtual void Reshape(int w, int h);
  virtual void KeyPress(unsigned char key, int x, int y);
};

class LNGdispatcher {
protected:
  static LNGframe *frame;
public:
  LNGdispatcher(LNGframe *aframe) {frame = aframe;};
  virtual ~LNGdispatcher() {};
  static void Timer(int dt) {frame->Timer(dt);};
  static void Idle(void) {frame->Idle();};
  static void Display(void) {frame->Display();};
  static void Reshape(int w, int h) {frame->Reshape(w, h);};
  static void KeyPress(unsigned char key, int x, int y){
    frame->KeyPress(key, x, y);
  };
};

#endif
