#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class RenderTexture;

class Texture
{
	friend class RenderTexture;
private:
	GLuint m_id;
	glm::vec2 m_size;

public:
	Texture();
	Texture(int width, int height);
	Texture(std::string file);
	glm::vec2 getSize();
	GLuint getId();

};
#endif