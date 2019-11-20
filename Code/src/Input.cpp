#include "Input.h"
#include <SDL2/SDL.h>

Input::Input()
{
	m_wKey = m_aKey = m_sKey = m_dKey = m_jKey = m_kKey = m_quit = false;

	m_oldMousePosition = m_mouseMovement = glm::vec2(0);
}

Input::~Input()
{
}

void Input::update(int _windowWidth, int _windowHeight)
{
	SDL_Event event = { 0 };
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	// Sets keys if held down

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_quit = true;
		}
		else
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_w) { m_wKey = true; }
				if (event.key.keysym.sym == SDLK_s) { m_sKey = true; }
				if (event.key.keysym.sym == SDLK_a) { m_aKey = true; }
				if (event.key.keysym.sym == SDLK_d) { m_dKey = true; }
				if (event.key.keysym.sym == SDLK_j) { m_jKey = true; }
				if (event.key.keysym.sym == SDLK_k) { m_kKey = true; }
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_w) { m_wKey = false; }
				if (event.key.keysym.sym == SDLK_s) { m_sKey = false; }
				if (event.key.keysym.sym == SDLK_a) { m_aKey = false; }
				if (event.key.keysym.sym == SDLK_d) { m_dKey = false; }
				if (event.key.keysym.sym == SDLK_j) { m_jKey = false; }
				if (event.key.keysym.sym == SDLK_k) { m_kKey = false; }
				break;
			default:
				break;
			}
		}
	}

	int Mid_X = _windowWidth / 2;
	int Mid_Y = _windowHeight/ 2;

	int posX, posY;
	// move the mouse back to the middle of the screen each frame
	SDL_WarpMouseInWindow(NULL, 400, 300);
	// get the current position of the cursor
	SDL_GetMouseState(&posX, &posY);

	m_mouseMovement.x = Mid_X - m_oldMousePosition.x;
	m_mouseMovement.y = Mid_Y - m_oldMousePosition.y;

	m_oldMousePosition = glm::vec2(posX, posY);
}

bool Input::getQuit()
{
	return m_quit;
}

bool Input::getKey(std::string _key)
{
	if (_key == "w")
	{
		return m_wKey;
	}
	else if (_key == "a")
	{
		return m_aKey;
	}
	else if (_key == "s")
	{
		return m_sKey;
	}
	else if (_key == "d")
	{
		return m_dKey;
	}
	else if (_key == "j")
	{
		return m_jKey;
	}
	else if (_key == "k")
	{
		return m_kKey;
	}
	return false;
}

glm::vec2 Input::getMouseMovement()
{
	return m_mouseMovement;
}
