#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class Texture
{
protected:
	GLuint m_id;
	glm::vec2 m_size;

public:
	Texture();
	Texture(int width, int height, bool _base);
	Texture(std::string file);
	glm::vec2 getSize();
	GLuint getId();

};
#endif