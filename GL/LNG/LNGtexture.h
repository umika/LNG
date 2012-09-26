/*
  LNGtexture.h
*/

#ifndef __LNGtexture_H__
#define __LNGtexture_H__

#include <GL/LNG/LNGut.h>

class LNGtexture {
protected:
public:
  LNGtexture();
  virtual ~LNGtexture();
};

class LNGloader {
public:
  bool flag_loading;
  std::deque<LNGtexture *> *textures;
public:
  LNGloader(int sz=0);
  virtual ~LNGloader();
  virtual void InitLoad(void);
  virtual void LoadNext(void);
};

#endif
