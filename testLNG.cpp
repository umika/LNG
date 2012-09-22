/*
  testLNG.cpp

  > cl testLNG.cpp LNGframe.cpp LNGclock.cpp -EHsc -I. \
    -link -LIBPATH:. -NODEFAULTLIB:libc

  -EHsc destroy local objects on catch any exception
  -NODEFAULTLIB:libc recent VC++ links 'libcmt.lib' instead of 'libc.lib'
  'GL/glut.h' 'glut32.lib' 'glut32.dll' from glut-3.7.6-bin.zip
  'GL/glpng.h' 'glpng.lib' from http://openports.se/graphics/glpng
*/

#include "testLNG.h"

TestLNG::TestLNG()
{
  // nothing
}

TestLNG::~TestLNG()
{
  // nothing
}

int main(int ac, char **av)
{
  TestLNG lng;
  return 0;
}
