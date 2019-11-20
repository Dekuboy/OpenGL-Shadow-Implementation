#include <string>
#include <glm/glm.hpp>

class Input
{
	// Checks if user quits

	bool m_quit;

	// All key bools hold whether a key is held down

	bool m_wKey;
	bool m_aKey;
	bool m_sKey;
	bool m_dKey;

	bool m_jKey;
	bool m_kKey;

	glm::vec2 m_oldMousePosition;
	glm::vec2 m_mouseMovement;
public:
	Input();
	~Input();

	void update(int _windowWidth, int _windowHeight);

	// Gets variable for stopping game
	bool getQuit();

	// Gets key state based on string
	bool getKey(std::string _key);

	// Gets mouse movement direction
	glm::vec2 getMouseMovement();
};