/*
  LNGtexture.cpp
*/

#include <GL/LNG/LNGtexture.h>

using namespace std;

string const LNGtexture::default_resource_dir("resource");
GLuint const LNGtexture::default_depth = 4;
LNGsize const LNGtexture::default_size(256, 256);

LNGtexture::LNGtexture(GLuint adepth, LNGsize asize) :
  flag_loading(true), flag_block(false),
  buffer(0), depth(adepth), size(asize), id(0)
{
#if defined( __TRACE_CONSTRUCTION__ ) || defined( _DEBUG )
  cout << "LNGtexture::LNGtexture" << endl;
#endif
  if(!buffer) buffer = new GLubyte[depth * asize.w * asize.h];
  if(!buffer) throw LNGexception("cannot allocate buffer for LNGtexture");
}

LNGtexture::~LNGtexture()
{
#if defined( __TRACE_DESTRUCTION__ ) || defined( _DEBUG )
  cout << "LNGtexture::~LNGtexture" << endl;
#endif
  Finalize();
}

void LNGtexture::Finalize(void)
{
#if defined( __TRACE_FINALIZATION__ ) || defined( _DEBUG )
  cout << "LNGtexture::Finalize" << endl;
#endif
  if(!flag_loading && buffer){
#if defined( __TRACE_FINALIZATION__ ) || defined( _DEBUG )
    cout << "finalize texture id: " << id << endl;
#endif
  }
  if(buffer){ delete[] buffer; buffer = 0; }
}

GLuint LNGtexture::Load(std::string &filename,
  std::string const &resource_dir)
{
  if(flag_block) return 0;
  flag_block = true;
#if defined( __TRACE_CREATION__ ) || defined( _DEBUG )
  cout << "LNGtexture::Load" << endl;
#endif
  string &filepath = LNGut::path_join(2, &resource_dir, &filename);
#if defined( __TRACE_CREATION__ ) || defined( _DEBUG )
  cout << "loading texture: " << filepath;
  cout.flush();
#endif
  glGenTextures(1, &id);
#if defined( __TRACE_CREATION__ ) || defined( _DEBUG )
  cout << " id: " << id << endl;
#endif
  if(!id) throw LNGexception(string("cannot generate texture: ") + filepath);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  pngRawInfo pri;
  if(!pngLoadRaw(filepath.c_str(), &pri))
    throw LNGexception(string("cannot load texture file: ") + filepath);
#ifdef _DEBUG
  cout << "File: " << filepath << endl;
  cout << " Width: " << pri.Width << endl;
  cout << " Height: " << pri.Height << endl;
  cout << " Depth: " << pri.Depth << endl;
  cout << " Alpha: " << pri.Alpha << endl;
  cout << " Components: " << pri.Components << endl;
  cout << " pData: " << (long)pri.Data << endl;
  cout << " pPalette: " << (long)pri.Palette << endl;
#endif
  if(pri.Data){
    if(pri.Components != depth && pri.Components != 1){
      ostringstream oss;
      oss << " texture depth error " << pri.Components;
      throw LNGexception(filepath + oss.str());
    }
    if(pri.Width != size.w){
      ostringstream oss;
      oss << " texture width error " << pri.Width << ", expected " << size.w;
      throw LNGexception(filepath + oss.str());
    }
    if(pri.Height != size.h){
      ostringstream oss;
      oss << " texture height error " << pri.Height << ", expected " << size.h;
      throw LNGexception(filepath + oss.str());
    }
    for(int y = 0; y < pri.Height; y++){
      for(int x = 0; x < pri.Width; x++){
        int s = depth - 1;
        int r = y * pri.Width + x;
        int q = r * depth;
        if(pri.Components == 1){
          int p = pri.Data[r] * s;
          for(int j = 0; j < s; j++) buffer[q + j] = pri.Palette[p + j];
        }else{
          for(int j = 0; j < s; j++) buffer[q + j] = pri.Data[q + j];
        }
        buffer[q + 3] = AlphaCallback(buffer[q], buffer[q + 1], buffer[q + 2]);
      }
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, pri.Width, pri.Height, 0,
      GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    free(pri.Data);
  }
  if(pri.Palette) free(pri.Palette);
  flag_loading = false;
  flag_block = false;
  return id;
}

GLubyte LNGtexture::AlphaCallback(GLubyte r, GLubyte g, GLubyte b)
{
  // GLubyte a = 255 - (r + g + b) / 3;
  GLubyte a = 255 * (r + g + b) / (255 * 3);
  return a & 0x00FF;
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
    if((*it)->flag_block) continue;
    GLuint id = (*it)->Load(string("72dpi.png"));
    exist = true;
    break; // load only 1 texture
  }
  if(!exist) flag_loading = false;
}
