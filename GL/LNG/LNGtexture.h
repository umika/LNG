/*
  LNGtexture.h
*/

#ifndef __LNGtexture_H__
#define __LNGtexture_H__

#include <GL/LNG/LNGut.h>

class LNGtexture {
public:
  static std::string const default_resource_dir;
  static GLuint const default_depth;
  static LNGsize const default_size;
  bool flag_loading;
  GLubyte *buffer;
  GLuint depth;
  LNGsize size;
  GLuint id;
public:
  LNGtexture(GLuint adepth=default_depth, LNGsize asize=default_size);
  virtual ~LNGtexture();
  virtual GLuint LoadTexture(std::string &filename,
    std::string const &resource_dir=default_resource_dir);
  virtual GLubyte *CustomData(LNGsize size, GLubyte *buf);
};

class LNGloader {
public:
  bool flag_loading;
  std::deque<LNGtexture *> *textures;
public:
  LNGloader(int size=0);
  virtual ~LNGloader();
  virtual void InitLoad(void);
  virtual void LoadNext(void);
};

#endif
