/*
  LNGcameleon_texture.cpp
*/

#include <LNG/LNGcameleon_texture.h>

using namespace std;

LNGcameleon_texture::LNGcameleon_texture(GLuint n, string &afilename,
  bool kb, bool ac, bool cp, bool cd, GLuint abpp, LNGsize asize,
  string const &aresource_dir) : LNGtexture(afilename,
  kb, ac, cp, cd, abpp, asize, aresource_dir), norm(n)
{
}

LNGcameleon_texture::~LNGcameleon_texture()
{
}

GLubyte *LNGcameleon_texture::CustomPixel(GLubyte *buf)
{
  return buf;
}
