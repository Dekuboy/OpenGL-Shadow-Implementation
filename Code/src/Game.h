#include <vector>
#include <memory>
#include "glm/glm.hpp"
#include <SDL2/SDL.h>

class ShaderProgram;
class RenderTexture;
class Input;
class Camera;
class GameObject;
class DepthBuffer;

class Game
{
	SDL_Window *m_window;

	std::shared_ptr<ShaderProgram> m_shinyShader;
	std::shared_ptr<ShaderProgram> m_environmentShader;

	std::shared_ptr<ShaderProgram> m_lightkeyShader;
	std::shared_ptr<ShaderProgram> m_nullShader;
	std::shared_ptr<ShaderProgram> m_blurShader;
	std::shared_ptr<ShaderProgram> m_mergeShader;

	std::shared_ptr<ShaderProgram> m_rippleShader;
	std::shared_ptr<ShaderProgram> m_staticShader;

	std::shared_ptr<RenderTexture> m_rt;
	std::shared_ptr<RenderTexture> m_lightkeyRt;
	std::shared_ptr<RenderTexture> m_blurRt;
	std::shared_ptr<RenderTexture> m_blur2Rt;
	std::shared_ptr<RenderTexture> m_mergeRt;

	std::shared_ptr<RenderTexture> m_rippleRt;

	std::shared_ptr<DepthBuffer> m_depthMap;

	// Stores input values from player
	std::shared_ptr<Input> m_keyState;
	// Stores game objects
	std::vector<std::shared_ptr<GameObject>> m_objects;
	// Stores Camera
	std::shared_ptr<Camera> m_camera;
	// Sdl window width
	int m_windowWidth;
	// Sdl window height
	int m_windowHeight;
public:
	Game();
	~Game();

	bool init();
	void gameLoop();
	void blur();
	void ripple(glm::vec3 _centre, float _rippleTime);
};