#include "Texture.h"

class RenderTexture : public Texture
{
  GLuint m_fbo;

public:
  RenderTexture(int width, int height);

  GLuint getFbId();
  void clear();

};
