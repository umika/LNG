/*
  LNGcameleon_texture.cpp
*/

#include <LNG/LNGcameleon_texture.h>

using namespace std;

LNGcameleon_texture::LNGcameleon_texture(string &afilename,
  bool kb, bool ac, bool cp, bool cd, GLuint abpp, LNGsize asize,
  string const &aresource_dir) : LNGtexture(afilename,
  kb, ac, cp, cd, abpp, asize, aresource_dir)
{
}

LNGcameleon_texture::~LNGcameleon_texture()
{
}
