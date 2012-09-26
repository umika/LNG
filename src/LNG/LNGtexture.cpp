/*
  LNGtexture.cpp
*/

#include <GL/LNG/LNGtexture.h>

using namespace std;

LNGtexture::LNGtexture()
{
}

LNGtexture::~LNGtexture()
{
}

LNGloader::LNGloader(int sz) : flag_loading(true)
{
  if(!textures) textures = new deque<LNGtexture *>(sz);
  if(!textures) throw LNGexception("cannot create std::deque<LNGtexture *>");
}

LNGloader::~LNGloader()
{
  if(textures) delete textures;
}

void LNGloader::InitLoad(void)
{
}

void LNGloader::LoadNext(void)
{
}
