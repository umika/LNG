/*
  LNGframe.cpp
*/

#include <GL/LNG/LNGframe.h>

using namespace std;

GLuint const LNGframe::default_fps = 60;
LNGsize const LNGframe::default_size(640, 480);
LNGpoint const LNGframe::default_pos(320, 240);

LNGframe *LNGdispatcher::frame = 0;

LNGframe::LNGframe(GLuint fps_desired) : dispatcher(0), fps(0)
{
  if(!fps) fps = new LNGclock(fps_desired);
  if(!dispatcher) dispatcher = new LNGdispatcher(this);
}

LNGframe::~LNGframe()
{
  if(dispatcher){ delete dispatcher; dispatcher = 0; }
  if(fps){ delete fps; fps = 0; }
}

void LNGframe::InitFrame(int *ac, char **av, std::string &title,
  LNGsize size, LNGpoint pos, GLuint mode)
{
#ifdef _DEBUG
  cout << "ac: " << *ac;
  for(int i = 0; i < *ac; i++) cout << ", " << av[i];
  cout << endl;
  cout << "size: " << size.w << ',' << size.h << endl;
  cout << "pos: " << pos.x << ',' << pos.y << endl;
#endif
  glutInit(ac, av);
  glutInitDisplayMode(mode);
  glutInitWindowSize(size.w, size.h);
  glutInitWindowPosition(pos.x, pos.y);
  glutCreateWindow(title.c_str());
  glutTimerFunc(0, dispatcher->Timer, 0);
  glutIdleFunc(dispatcher->Idle);
  glutDisplayFunc(dispatcher->Display);
  glutReshapeFunc(dispatcher->Reshape);
  glutKeyboardFunc(dispatcher->KeyPress);
  InitGL();
  glutMainLoop();
}

void LNGframe::InitGL(void)
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST); // glutInitDisplayMode() GLUT_DEPTH
  LoadTextures();
}

void LNGframe::Timer(int dt)
{
  if(fps){
    GLuint f = fps->desired();
    if(dt > f) dt = 0;
    glutTimerFunc(1000 / f, dispatcher->Timer, ++dt);
    fps->FPS();
  }
  Update();
}

void LNGframe::Idle(void)
{
}

void LNGframe::Update(void)
{
  glutPostRedisplay();
}

void LNGframe::ChangeView(void)
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void LNGframe::DisplayBefore(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LNGframe::DisplayDraw(void)
{
  glDisable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glColor4f(0.0, 1.0, 0.0, 0.8);
  glBegin(GL_TRIANGLES);
    glVertex3f(-0.25, -0.25, -0.75);
    glVertex3f( 0.25, -0.25, -0.75);
    glVertex3f( 0.00,  0.25, -0.75);
  glEnd();
  glColor4f(0.0, 1.0, 1.0, 0.6);
  glBegin(GL_TRIANGLES);
    glVertex3f( 0.00, -0.25, -0.50);
    glVertex3f( 0.50, -0.25, -0.50);
    glVertex3f( 0.25,  0.25, -0.50);
  glEnd();
  glColor4f(1.0, 0.0, 0.0, 0.4);
  glBegin(GL_TRIANGLES);
    glVertex3f( 0.25, -0.25, -0.25);
    glVertex3f( 0.75, -0.25, -0.25);
    glVertex3f( 0.50,  0.25, -0.25);
  glEnd();
  glColor4f(1.0, 0.0, 0.0, 0.9);
  glRasterPos3f(0.0, 0.0, 0.0);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '*');
  glDisable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
}

void LNGframe::DisplayAfter(void)
{
  // glFlush(); // glutInitDisplayMode() GLUT_SINGLE ?
  glutSwapBuffers(); // glutInitDisplayMode() GLUT_DOUBLE (double buffering)
}

void LNGframe::Display(void)
{
  DisplayBefore();
  ChangeView();
  ChangeAngle();
  if(fps) fps->FPSdisplay();
  DisplayDraw();
  DisplayAfter();
}

void LNGframe::Reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  Ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
  Perspective(w, h);
  Display(); // not use Update()
}

void LNGframe::KeyPress(unsigned char key, int x, int y)
{
  if(key == 27){ // ESC
    glutDestroyWindow(glutGetWindow());
    exit(0);
  }
}

void LNGframe::MouseAction(int button, int state, int x, int y)
{
  MouseMove(button, state, x, y);
  if(button == GLUT_LEFT_BUTTON){
    if(state == GLUT_DOWN) LeftDown(button, state, x, y);
    else if(state == GLUT_UP) LeftUp(button, state, x, y);
    else ; // through
  }
  if(button == GLUT_MIDDLE_BUTTON){ // not use else if
    if(state == GLUT_DOWN) MiddleDown(button, state, x, y);
    else if(state == GLUT_UP) MiddleUp(button, state, x, y);
    else ; // through
  }
  if(button == GLUT_RIGHT_BUTTON){ // not use else if
    if(state == GLUT_DOWN) RightDown(button, state, x, y);
    else if(state == GLUT_UP) RightUp(button, state, x, y);
    else ; // through
  }
}
