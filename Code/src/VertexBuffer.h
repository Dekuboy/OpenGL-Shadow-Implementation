#include <glm/glm.hpp>
#include <vector>
#include <GL/glew.h>

class VertexBuffer
{
private:
	GLuint m_id;
	int m_components;
	std::vector <GLfloat> m_data;
	bool m_dirty;

public:
	VertexBuffer();

	void add(glm::vec2 value);
	void add(glm::vec3 value);
	void add(glm::vec4 value);

	int getComponents();
	int getDataSize();
	GLuint getId();
};