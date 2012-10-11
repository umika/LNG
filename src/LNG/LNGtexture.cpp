/*
  LNGtexture.cpp
*/

#include <GL/LNG/LNGtexture.h>

using namespace std;

string const LNGtexture::default_resource_dir("resource");
GLuint const LNGtexture::default_bytes_par_pixel = 4;
LNGsize const LNGtexture::default_size(256, 256);

LNGtexture::LNGtexture(string &afilename,
  bool ac, bool cp, bool cd, bool kb, GLuint abpp, LNGsize asize,
  string const &aresource_dir) : loading(true), blocking(false),
  use_alphacallback(ac), use_custompixel(cp), use_customdata(cd),
  keep_buffer(kb), buffer(0), bytes_par_pixel(abpp), size(asize), id(0),
  filename(afilename), resource_dir(aresource_dir)
{
#if defined( __TRACE_CONSTRUCTION__ ) || defined( _DEBUG )
  cout << "LNGtexture::LNGtexture" << endl;
#endif
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
  if(!loading && buffer){
#if defined( __TRACE_FINALIZATION__ ) || defined( _DEBUG )
    cout << "finalize texture id: " << id << endl;
#endif
  }
  if(buffer){ delete[] buffer; buffer = 0; }
}

GLuint LNGtexture::Load(void)
{
  if(blocking) return 0;
  blocking = true;
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
  cout << " id: " << setw(4) << setfill(' ') << dec << right << id << endl;
#endif
  if(!id) throw LNGexception(string("cannot generate texture: ") + filepath);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  LNGpng png;
  if(!png.LoadRaw(filepath))
    throw LNGexception(string("cannot load texture file: ") + filepath);
#ifdef _DEBUG
  cout << "File: " << filepath << endl;
  cout << " id: " << setw(4) << setfill(' ') << dec << right << id << endl;
  cout << " width, height: " << png.size.w << ", " << png.size.h << endl;
  cout << " depth, col_type: " << png.depth << ", " << png.col_type << endl;
  cout << " interlace_type: " << png.interlace_type << endl;
  cout << " compress_type: " << png.compress_type << endl;
  cout << " filter_type: " << png.filter_type << endl;
  cout << " png depth: " << png.png_depth << endl;
  cout << " p_depth, b_depth: " << png.p_depth << ", " << png.b_depth << endl;
  cout << " pals, num_pals: " << png.pals << ", " << png.num_pals << endl;
  cout << " alpha: " << png.alpha << endl;
  cout << " pData: " << setw(8) << setfill('0') << hex << right;
  cout << (png_uint_32)png.image << endl;
  cout << " pPalette: " << setw(8) << setfill('0') << hex << right;
  cout << (png_uint_32)png.palette << endl;
#endif
  if(png.image){
    if(png.pals && !png.palette)
      throw LNGexception(filepath + " texture palette error NULL");
    if(!png.pals && png.alpha != 4){ // != bytes_par_pixel){
      ostringstream oss;
      oss << " texture depth error " << png.depth;
      throw LNGexception(filepath + oss.str());
    }
    // bytes_par_pixel = png.depth;
#ifdef _DEBUG
    if(png.size.w != size.w){
      ostringstream oss;
      oss << " texture width error " << png.size.w << ", expected " << size.w;
      throw LNGexception(filepath + oss.str());
    }
    if(png.size.h != size.h){
      ostringstream oss;
      oss << " texture height error " << png.size.h << ", expected " << size.h;
      throw LNGexception(filepath + oss.str());
    }
#endif
    size.w = png.size.w;
    size.h = png.size.h;
    GLubyte *buf = 0;
    if(!buf) buf = new GLubyte[bytes_par_pixel * size.w * size.h];
    if(!buf) throw LNGexception("cannot allocate buf for LNGtexture");
#ifdef _DEBUG // dump index color 125 (256) to check a palette (exception)
    if(png.pals){
      ostringstream oss;
      oss << "index color map of texture: " << filepath;
      for(int j = 0; j < png.num_pals; j++){
        if(!(j % 8))
          oss << endl << setw(4) << setfill(' ') << dec << right << j << ": ";
        if(j % 8) oss << " ";
        for(int i = 0; i < sizeof(png_color) / sizeof(png_byte); i++){
          oss << setw(2) << setfill('0') << hex << right;
          oss << (png_uint_32)*((GLubyte *)&png.palette[j] + i);
        }
      }
      throw LNGexception(oss.str());
    }
#endif
    for(int y = 0; y < size.h; y++){
      for(int x = 0; x < size.w; x++){
        int s = bytes_par_pixel - 1;
        int r = y * size.w + x;
        int q = r * bytes_par_pixel;
        if(png.pals){
          int p = png.image[r];
          for(int j = 0; j < sizeof(png_color) / sizeof(png_byte); j++)
            buf[q + j] = *((GLubyte *)&png.palette[p] + j);
        }else{
          for(int j = 0; j < s; j++) buf[q + j] = png.image[q + j];
        }
        if(use_alphacallback)
          buf[q + 3] = AlphaCallback(buf[q + 0], buf[q + 1], buf[q + 2]);
        else buf[q + 3] = png.pals ? 255 : png.image[q + 3];
        if(use_custompixel) CustomPixel(&buf[q]);
      }
    }
    if(use_customdata) CustomData(buf);
    if(keep_buffer){
      if(!buffer) buffer = new GLubyte[bytes_par_pixel * size.w * size.h];
      if(!buffer) throw LNGexception("cannot allocate buffer for LNGtexture");
      for(int y = 0; y < size.h; y++){
        for(int x = 0; x < size.w; x++){
          int q = (y * size.w + x) * bytes_par_pixel;
          for(int j = 0; j < bytes_par_pixel; j++) buffer[q + j] = buf[q + j];
        }
      }
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, size.w, size.h, 0,
      GL_RGBA, GL_UNSIGNED_BYTE, buf);
    if(buf){ delete[] buf; buf = 0; }
  }
  loading = false;
  blocking = false;
  return id;
}

LNGloader::LNGloader(int size) : loading(true)
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
  char *fn[] = {"f0.png", "f1.png", "f2.png", "f3.png", "f4.png", "f5.png",
    "72dpi.png", "72dpi_ascii_reigasou_16x16.png"};
  for(int i = 0; i < sizeof(fn) / sizeof(fn[0]); i++)
    textures->push_back(new LNGtexture(string(fn[i])));
}

void LNGloader::LoadNext(void)
{
  bool exist = false;
  deque<LNGtexture *>::iterator it;
  for(it = textures->begin(); it != textures->end(); ++it){
    if(!(*it)->loading) continue;
    if((*it)->blocking) continue;
    GLuint id = (*it)->Load();
    exist = true;
    break; // load only 1 texture
  }
  if(!exist) loading = false;
}
