/*
  LNGtypes.h
*/

#ifndef __LNGtypes_H__
#define __LNGtypes_H__

#include <iostream>
#include <sstream>
#include <string>
#include <cstdarg>
#include <cstdlib>

#include <GL/glut.h>
#include <GL/glpng.h>

typedef struct LNGsize {
  GLuint w, h;
public:
  LNGsize(GLuint aw, GLuint ah) : w(aw), h(ah) {};
} LNGsize;

typedef struct LNGpoint {
  GLuint x, y;
public:
  LNGpoint(GLuint ax, GLuint ay) : x(ax), y(ay) {};
} LNGpoint;

#endif
