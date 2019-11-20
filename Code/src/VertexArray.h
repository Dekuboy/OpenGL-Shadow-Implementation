#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

class VertexBuffer;

class VertexArray
{
  GLuint m_id;
  bool m_dirty;
  std::vector<std::shared_ptr<VertexBuffer>> m_buffers;

  void splitStringWhitespace(std::string& input, std::vector<std::string>& output);
  void splitString(std::string& input, char splitter, std::vector<std::string>& output);

public:
  VertexArray();
  VertexArray(std::string path);
  void setBuffer(std::string attribute, std::shared_ptr<VertexBuffer> buffer);
  int getVertexCount();
  GLuint getId();

};
