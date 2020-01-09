#include <GL/glew.h>
#include <glm/glm.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

class VertexArray;
class Texture;
class RenderTexture;
class DepthBuffer;

struct Sampler
{
	GLint m_id;
	std::shared_ptr<Texture> m_texture;
};

class ShaderProgram
{
private:
	GLuint m_id;
	std::vector <Sampler> m_samplers;
	glm::vec4 m_viewport;
	std::shared_ptr<VertexArray> m_simpleShape;

public:
	ShaderProgram();
	ShaderProgram(std::string vert, std::string frag);
	ShaderProgram(std::string vert, std::string frag, std::string geom);

	void draw();
	void draw(std::shared_ptr<RenderTexture> renderTexture);
	void draw(std::shared_ptr<VertexArray> vertexArray);
	void draw(std::shared_ptr<RenderTexture> renderTexture, std::shared_ptr<VertexArray> vertexArray);

	void setUniform(std::string uniform, glm::vec4 value);
	void setUniform(std::string uniform, glm::vec3 value);
	void setUniform(std::string uniform, float value);
	void setUniform(std::string uniform, std::shared_ptr<Texture> texture);
	void setUniform(std::string uniform, glm::mat4 matrix);
	void setUniform(std::string uniform, std::vector<glm::mat4> matrices);
	void setUniform(std::string uniform, std::shared_ptr<DepthBuffer> depth);

	GLuint getId();
	void setViewport(glm::vec4 viewport);
};