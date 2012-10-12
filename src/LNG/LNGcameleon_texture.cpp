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
  if(norm && buf[0] >= 96 && buf[1] >= 96 && buf[2] >= 96){
    buf[0] = norm & 1 ? buf[0] : 0;
    buf[1] = norm & 2 ? buf[1] : 0;
    buf[2] = norm & 4 ? buf[2] : 0;
  }
  return buf;
}
