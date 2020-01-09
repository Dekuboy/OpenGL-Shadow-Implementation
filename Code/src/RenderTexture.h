#ifndef RENDTEXTURE_H
#define RENDTEXTURE_H
#include "Texture.h"
class DepthBuffer;
class DepthCube;

class RenderTexture : public Texture
{
protected:
  GLuint m_fbo;

public:
  RenderTexture(int width, int height);
  RenderTexture(int width, int height, bool _base);

  GLuint getFbId();
  virtual void clear();

};

#endif