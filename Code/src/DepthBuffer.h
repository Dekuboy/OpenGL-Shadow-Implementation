#include <GL/glew.h>
#include <glm/glm.hpp>

class DepthBuffer
{
private:
	GLuint m_id;
	GLuint m_fbo;
	glm::vec2 m_size;

	void init();

public:
	DepthBuffer();
	DepthBuffer(int width, int height);
	glm::vec2 getSize();
	GLuint getId();
	GLuint getFbId();
	void clear();
};