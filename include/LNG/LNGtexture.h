/*
  LNGtexture.h
*/

#ifndef __LNGtexture_H__
#define __LNGtexture_H__

#include <LNG/LNGpng.h>

class LNGtexture {
public:
  static std::string const default_resource_dir;
  static GLuint const default_bytes_par_pixel;
  static LNGsize const default_size;
  bool loading, blocking;
  bool use_alphacallback, use_custompixel, use_customdata, keep_buffer;
  GLubyte *buffer;
  GLuint bytes_par_pixel;
  LNGsize size;
  GLuint id;
  std::string filename, resource_dir;
public:
  // kb: keep_buffer, ac: alphacallback, cp: custompixel, cd: customdata
  LNGtexture(std::string &afilename,
    bool kb=false, bool ac=false, bool cp=false, bool cd=false,
    GLuint abpp=default_bytes_par_pixel, LNGsize asize=default_size,
    std::string const &aresource_dir=default_resource_dir);
  virtual ~LNGtexture();
  virtual void Finalize(void);
  virtual GLuint Load(void);
  virtual GLubyte AlphaCallback(GLubyte r, GLubyte g, GLubyte b)
    {return (255 * (r + g + b) / (255 * 3)) & 0x00FF;}
  virtual GLubyte *CustomPixel(GLubyte *buf) {return buf;}
  virtual GLubyte *CustomData(GLubyte *buf) {return buf;}
};

class LNGloader {
public:
  bool loading;
  std::deque<LNGtexture *> *textures;
public:
  LNGloader(int size=0);
  virtual ~LNGloader();
  virtual void LoadNext(void);
};

#endif
