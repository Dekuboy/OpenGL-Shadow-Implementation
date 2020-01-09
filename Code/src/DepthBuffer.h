#include <GL/glew.h>
#include <glm/glm.hpp>
#include "RenderTexture.h"

class DepthBuffer : public RenderTexture
{
public:
	DepthBuffer(int width, int height);

	void clear();
};