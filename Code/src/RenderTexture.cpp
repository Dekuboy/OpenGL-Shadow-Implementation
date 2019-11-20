#include "RenderTexture.h"

RenderTexture::RenderTexture(int width, int height) : Texture(width, height)
{
  glGenFramebuffers(1, &m_fbo);
  if(!m_fbo) throw std::exception();
  glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_id, 0);

  GLuint rbo = 0;
  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint RenderTexture::getFbId()
{
  return m_fbo;
}

void RenderTexture::clear()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
