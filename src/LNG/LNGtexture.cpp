/*
  LNGtexture.cpp
*/

#include <GL/LNG/LNGtexture.h>

using namespace std;

string const LNGtexture::default_resource_dir("resource");
GLuint const LNGtexture::default_depth = 4;
LNGsize const LNGtexture::default_size(256, 256);

LNGtexture::LNGtexture(GLuint adepth, LNGsize asize) : flag_loading(true),
  buffer(0), depth(adepth), size(asize), id(0)
{
  if(!buffer) buffer = new GLubyte[depth * asize.w * asize.h];
  if(!buffer) throw LNGexception("cannot allocate buffer for LNGtexture");
}

LNGtexture::~LNGtexture()
{
  if(buffer) delete[] buffer;
}

GLuint LNGtexture::LoadTexture(std::string &filename,
  std::string const &resource_dir)
{
  string &filepath = LNGut::path_join(2, &resource_dir, &filename);
  cout << filepath << endl;
  id = 1;
  return id;
}

GLubyte *LNGtexture::CustomData(LNGsize size, GLubyte *buf)
{
  return buf;
}

LNGloader::LNGloader(int size) : flag_loading(true)
{
  if(!textures) textures = new deque<LNGtexture *>(size);
  if(!textures) throw LNGexception("cannot create std::deque<LNGtexture *>");
}

LNGloader::~LNGloader()
{
  if(textures){
    while(!textures->empty()){
//      LNGtexture *texture = textures[0];
      LNGtexture *texture = textures->at(0);
      textures->pop_front();
// #ifdef _DEBUG
      cout << "delete texture: " << texture->id << endl;
// #endif
      delete texture;
    }
    delete textures;
  }
}

void LNGloader::InitLoad(void)
{
  for(int i = 0; i < 3; i++){
    LNGtexture *texture = new LNGtexture();
    textures->push_back(texture);
    GLuint id = texture->LoadTexture(string("72dpi.png"));
// #ifdef _DEBUG
    cout << "create texture: " << id << endl;
// #endif
  }
}

void LNGloader::LoadNext(void)
{
}
