#include <GL/glew.h>
#include <glm/glm.hpp>

class DepthBuffer
{
private:
	GLuint m_id;
	glm::vec2 m_size;

public:
	DepthBuffer();
	DepthBuffer(int width, int height);
	glm::vec2 getSize();
	GLuint getId();

};