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
  Finalize();
}

void LNGtexture::Finalize(void)
{
  if(buffer){ delete[] buffer; buffer = 0; }
}

GLuint LNGtexture::Load(std::string &filename,
  std::string const &resource_dir)
{
  string &filepath = LNGut::path_join(2, &resource_dir, &filename);
#ifdef _DEBUG
  cout << filepath << endl;
#endif
  id = 1;
  flag_loading = false;
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
      // may use (*textures)[0]; or textures->at(0);
      LNGtexture *texture = textures->front();
      textures->pop_front();
#ifdef _DEBUG
      cout << "delete texture: " << texture->id << endl;
#endif
      texture->Finalize();
      delete texture;
    }
    delete textures;
  }
}

void LNGloader::InitLoad(void)
{
  for(int i = 0; i < 3; i++) textures->push_back(new LNGtexture());
}

void LNGloader::LoadNext(void)
{
  bool exist = false;
  deque<LNGtexture *>::iterator it;
  for(it = textures->begin(); it != textures->end(); ++it){
    if(!(*it)->flag_loading) continue;
    GLuint id = (*it)->Load(string("72dpi.png"));
#ifdef _DEBUG
    cout << "loading texture: " << id << endl;
#endif
    if(!id){
      throw LNGexception("cannot load texture");
    }else{
      exist = true;
      break; // load only 1 texture
    }
  }
  if(!exist) flag_loading = false;
}
