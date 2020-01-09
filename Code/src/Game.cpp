#include "GameWrap.h"
#include <ctime>
#include <iostream>

Game::Game()
{
	if (init())
	{
		m_environmentShader =
			std::make_shared<ShaderProgram>("../shaders/simple.vert", "../shaders/phong.frag");

		m_lightkeyShader =
			std::make_shared<ShaderProgram>("../shaders/lightkeypass.vert", "../shaders/lightkeypass.frag");
		m_nullShader =
			std::make_shared<ShaderProgram>("../shaders/nullpass.vert", "../shaders/nullpass.frag");
		m_blurShader =
			std::make_shared<ShaderProgram>("../shaders/blur.vert", "../shaders/blur.frag");
		m_mergeShader =
			std::make_shared<ShaderProgram>("../shaders/mergepass.vert", "../shaders/mergepass.frag");
		m_rippleShader =
			std::make_shared<ShaderProgram>("../shaders/ripple.vert", "../shaders/ripple.frag");
		m_staticShader =
			std::make_shared<ShaderProgram>("../shaders/simple.vert", "../shaders/static.frag");

		m_rt =
			std::make_shared<RenderTexture>(512, 512);
		m_lightkeyRt =
			std::make_shared<RenderTexture>(512, 512);
		m_blurRt =
			std::make_shared<RenderTexture>(512, 512);
		m_blur2Rt =
			std::make_shared<RenderTexture>(512, 512);
		m_mergeRt =
			std::make_shared<RenderTexture>(512, 512);
		m_rippleRt = std::make_shared<RenderTexture>(512, 512);

		m_lightPosition = glm::vec3(0, 5, -10);
		m_lightDirection = glm::normalize(glm::vec3(0, 1, 1));

		m_environmentShader->setUniform("in_Projection", glm::perspective(glm::radians(45.0f),
			(float)m_windowWidth / (float)m_windowHeight, 0.1f, 100.f));
		m_environmentShader->setUniform("in_Emissive", glm::vec3(0, 0, 0));
		m_environmentShader->setUniform("in_Ambient", glm::vec3(0.1, 0.1, 0.1));
		//m_environmentShader->setUniform("in_LightPos", m_lightPosition);
		m_environmentShader->setUniform("in_LightDir", m_lightDirection);

		m_staticShader->setUniform("in_Projection", glm::ortho(0.0f,
			(float)m_windowWidth, 0.0f, (float)m_windowHeight, -1.0f, 1.0f));

		//m_depthMap = std::make_shared<DepthBuffer>(1024, 1024);

		//float near_plane = 1.0f, far_plane = 30.0f;
		//glm::mat4 lightProjection = glm::perspective(glm::radians(90.0f),
		//	1.0f, 8.0f, 30.0f);

		//glm::mat4 lightView = glm::lookAt(m_lightPosition,
		//	glm::vec3(0.0f, -2.1f, -20.0f),
		//	glm::vec3(0.0f, 1.0f, 0.0f));

		//glm::mat4 lightSpaceMatrix = lightProjection * lightView;

		//m_depthShader = std::make_shared<ShaderProgram>("../shadows/shadow.vert", "../shadows/shadow.frag");
		//m_shadowShader = std::make_shared<ShaderProgram>("../shadows/shadowmap.vert", "../shadows/spsmap.frag");

		//m_depthShader->setUniform("in_LightSpace", lightSpaceMatrix);

		//m_shadowShader->setUniform("in_LightSpace", lightSpaceMatrix);
		//m_shadowShader->setUniform("in_Projection", glm::perspective(glm::radians(45.0f),
		//	(float)m_windowWidth / (float)m_windowHeight, 0.1f, 100.f));
		//m_shadowShader->setUniform("in_Ambient", glm::vec3(0.1, 0.1, 0.1));
		//m_shadowShader->setUniform("in_LightPos", m_lightPosition);

		m_depthCube = std::make_shared<DepthCube>(1024, 1024);

		float aspect = (float)1024 / (float)1024;
		float near = 1.0f;
		float far = 50.0f;
		glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), aspect, near, far);

		std::vector<glm::mat4> shadowTransforms;
		shadowTransforms.push_back(shadowProj *
			glm::lookAt(m_lightPosition, m_lightPosition + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
		shadowTransforms.push_back(shadowProj *
			glm::lookAt(m_lightPosition, m_lightPosition + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
		shadowTransforms.push_back(shadowProj *
			glm::lookAt(m_lightPosition, m_lightPosition + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
		shadowTransforms.push_back(shadowProj *
			glm::lookAt(m_lightPosition, m_lightPosition + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
		shadowTransforms.push_back(shadowProj *
			glm::lookAt(m_lightPosition, m_lightPosition + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
		shadowTransforms.push_back(shadowProj *
			glm::lookAt(m_lightPosition, m_lightPosition + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

		m_depthShader = std::make_shared<ShaderProgram>("../shadows/shadowCube.vert", 
			"../shadows/shadowCube.frag", "../shadows/shadowCube.geom");
		m_shadowShader = std::make_shared<ShaderProgram>("../shadows/cubeMap.vert", "../shadows/cubeMap.frag");

		//for (int i = 0; i < 6; ++i)
		//	m_depthShader->setUniform("in_LightSpace[" + std::to_string(i) + "]", shadowTransforms[i]);
		m_depthShader->setUniform("in_LightSpace", shadowTransforms);
		m_depthShader->setUniform("in_LightPos", m_lightPosition);
		m_depthShader->setUniform("in_FarPlane", far);

		m_shadowShader->setUniform("in_Projection", glm::perspective(glm::radians(45.0f),
			(float)m_windowWidth / (float)m_windowHeight, 0.1f, 100.f));
		m_shadowShader->setUniform("in_Ambient", glm::vec3(0.1, 0.1, 0.1));
		m_shadowShader->setUniform("in_LightPos", m_lightPosition);
		m_shadowShader->setUniform("in_FarPlane", far);

		SDL_ShowCursor(false);

		gameLoop();
	}
}

Game::~Game()
{

}

bool Game::init()
{
	m_windowWidth = 800;
	m_windowHeight = 600;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception();
		return false;
	}

	m_window = SDL_CreateWindow("Triangle",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		m_windowWidth, m_windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(m_window))
	{
		throw std::exception();
		return false;
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
		return false;
	}
	return true;
}

void Game::gameLoop()
{
	std::cout << glGetString(GL_VERSION);
	// Make base objects vaos and textures
	std::shared_ptr<VertexArray> hallShape =
		std::make_shared<VertexArray>("../objs/re_hall_baked.obj");
	std::shared_ptr<Texture> hallTexture =
		std::make_shared<Texture>("../images/re_hall_diffuse.png");
	std::shared_ptr<VertexArray> shape =
		std::make_shared<VertexArray>("../objs/curuthers.obj");
	std::shared_ptr<Texture> texture =
		std::make_shared<Texture>("../images/curuthers_diffuse.png");

	std::shared_ptr<VertexArray> crateS =
		std::make_shared<VertexArray>("../objs/Crate1.obj");
	std::shared_ptr<Texture> crateT =
		std::make_shared<Texture>("../images/crate_1.png");

	std::shared_ptr<Texture> healthBar =
		std::make_shared<Texture>("../images/health_bar.png");

	// Set Input ptr
	m_keyState = std::make_shared<Input>();

	// CAMERA VARIABLES
	glm::vec3 cameraPosition(0.0f, 0.0f, -2.0f);
	glm::vec2 camAngle(0.0f, 0.0f);
	glm::vec3 camBScale(0.3f, 0.3f, 0.3f);
	float camSpeed = 0.08f;

	// Create Curuthers
	float angle = 0.0f;
	Model tempModel;
	tempModel.m_position = glm::vec3(0.0f, -2.1f, -20.0f);
	tempModel.m_rotation = glm::vec3(0, angle, 0);

	std::shared_ptr<GameObject> curuthers =
		std::make_shared<GameObject>(texture, shape, m_shadowShader);

	curuthers->setInitialModel(tempModel);

	// Create Mansion

	tempModel.m_position = glm::vec3(2.0f, -2.0f, -16.0f);
	tempModel.m_rotation = glm::vec3(0.0f, 90.0f, 0.0f);

	std::shared_ptr<GameObject> mansion =
		std::make_shared<GameObject>(hallTexture, hallShape, m_shadowShader);

	mansion->setInitialModel(tempModel);

	// LightCrate

	tempModel.m_position = m_lightPosition;

	std::shared_ptr<GameObject> crate =
		std::make_shared<GameObject>(crateT, crateS, m_shadowShader);

	crate->setInitialModel(tempModel);

	// Set mansion hitboxes

	tempModel.m_position = glm::vec3(20, 5, -20);
	tempModel.m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	tempModel.m_scale = glm::vec3(0.3, 5, 20);
	mansion->addModel(tempModel);

	tempModel.m_position = glm::vec3(-20, 5, -20);
	tempModel.m_scale = glm::vec3(0.3, 5, 20);
	mansion->addModel(tempModel);

	tempModel.m_position = glm::vec3(0, 5, 0);
	tempModel.m_scale = glm::vec3(20, 5, 0.3);
	mansion->addModel(tempModel);

	tempModel.m_position = glm::vec3(0, 5, -40);
	tempModel.m_scale = glm::vec3(20, 5, 0.3);
	mansion->addModel(tempModel);

	// Time Variables
	float currentTime, deltaTime, lastTime = 0.0f;

	// Ripple variables

	float rippleTime = 0.0f;

	bool quit = false;
	while (!quit)
	{
		// Reset variables per update

		currentTime = SDL_GetTicks();
		deltaTime = (float)(currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		m_rt->clear();
		m_depthCube->clear();

		m_keyState->update(m_windowWidth, m_windowHeight);

		quit = m_keyState->getQuit();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update camAngle using input
		camAngle += camSpeed * m_keyState->getMouseMovement();
		if (camAngle.y > 85.0f)
		{
			camAngle.y = 85.0f;
		}
		else if (camAngle.y < -85.0f)
		{
			camAngle.y = -85.0f;
		}
		if (camAngle.x > 360.0f)
		{
			camAngle.x -= 360.0f;
		}
		else if (camAngle.x < -360.0f)
		{
			camAngle.x += 360.0f;
		}

		// Create Arbitrary Matrix
		glm::mat4 tempMat(1.0f);

		// Rotate it by Angle
		tempMat = glm::rotate(tempMat, glm::radians(camAngle.x), glm::vec3(0, 1, 0));

		// Move Forward 1 Unit

		if (m_keyState->getKey("w")) { tempMat = glm::translate(tempMat, glm::vec3(0, 0, -1)); }
		if (m_keyState->getKey("s")) { tempMat = glm::translate(tempMat, glm::vec3(0, 0, 1)); }
		if (m_keyState->getKey("a")) { tempMat = glm::translate(tempMat, glm::vec3(-1, 0, 0)); }
		if (m_keyState->getKey("d")) { tempMat = glm::translate(tempMat, glm::vec3(1, 0, 0)); }
		if (m_keyState->getKey("j")) { rippleTime = 0.0f; }

		// Apply to an initial position
		glm::vec3 fwd = tempMat * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		// Normalize to get the unit vector
		if (fwd != glm::vec3(0.0f, 0.0f, 0.0f))
		{
			fwd = 0.5f * glm::normalize(fwd);
			cameraPosition += fwd;
		}

		// Check Collision

		int wallNo = mansion->getModelTotal();
		for (int i = 0; i < wallNo; i++)
		{
			tempModel = mansion->getModel(i);
			if (PFG::axisABoundingBox(cameraPosition, tempModel.m_position,
				camBScale, tempModel.m_scale))
			{
				cameraPosition -= fwd;
				i = wallNo;
			}
		}

		// Create shadows
		//glCullFace(GL_FRONT);
		mansion->draw(m_depthCube, m_depthShader);
		curuthers->draw(m_depthCube, m_depthShader);
		m_shadowShader->setUniform("in_DepthMap", m_depthCube);

		//glCullFace(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Set Camera
		glm::mat4 camModel(1.0f);
		camModel = glm::translate(camModel, cameraPosition);
		camModel = glm::rotate(camModel, glm::radians(camAngle.x), glm::vec3(0, 1, 0));
		camModel = glm::rotate(camModel, glm::radians(camAngle.y), glm::vec3(1, 0, 0));
		m_environmentShader->setUniform("in_View", glm::inverse(camModel));
		m_staticShader->setUniform("in_View", glm::inverse(camModel));
		m_shadowShader->setUniform("in_View", glm::inverse(camModel));

		// Draw the mansion
		mansion->draw(m_rt);

		// Draw the cat
		curuthers->draw(m_rt);

		// Draw LightCrate
		crate->draw(m_rt);

		glDisable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Create bloom

		blur();

		// Draw ripple

		ripple(glm::vec3(0.5f, -0.5f, 0.0f), rippleTime);

		// Draw to window

		m_nullShader->setViewport(glm::vec4(0, 0, m_windowWidth, m_windowHeight));
		m_nullShader->setUniform("in_Texture", m_rt);
		m_nullShader->draw();

		// Draw HUD to window

		glm::mat4 hudModel = camModel;
		hudModel = glm::translate(hudModel, glm::vec3(100.0f, 550.0f, 0.0f));
		hudModel = glm::scale(hudModel, glm::vec3(100, 50, 1));
		m_staticShader->setUniform("in_Model", hudModel);
		m_staticShader->setUniform("in_Texture", healthBar);
		m_staticShader->draw();

		angle++;
		tempModel = curuthers->getInitialModel();
		tempModel.m_rotation = glm::vec3(0.0f, angle, 0.0f);
		curuthers->setInitialModel(tempModel);

		SDL_GL_SwapWindow(m_window);

		// Cap framerate

		if (deltaTime < (1.0f / 60.0f))
		{
			SDL_Delay((unsigned int)(((1.0f / 60.0f) - deltaTime)*1000.0f));
		}
		lastTime = currentTime;

		// Update time variables

		rippleTime += deltaTime;
	}

	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::blur()
{
	m_lightkeyShader->setUniform("in_Texture", m_rt);
	m_lightkeyShader->draw(m_lightkeyRt);

	m_blurShader->setUniform("in_Texture", m_lightkeyRt);
	m_blurShader->draw(m_blurRt);

	for (int i = 0; i < 6; i++)
	{
		m_blurShader->setUniform("in_Texture", m_blurRt);
		m_blurShader->draw(m_blur2Rt);

		m_blurShader->setUniform("in_Texture", m_blur2Rt);
		m_blurShader->draw(m_blurRt);
	}

	m_mergeShader->setUniform("in_TextureA", m_rt);
	m_mergeShader->setUniform("in_TextureB", m_blurRt);
	m_mergeShader->draw(m_mergeRt);
}

void Game::ripple(glm::vec3 _centre, float _rippleTime)
{
	glm::vec3 shock(10.0f, 0.8f, 0.1f);

	m_rippleShader->setUniform("in_Centre", _centre);
	m_rippleShader->setUniform("in_Shock", shock);
	m_rippleShader->setUniform("in_Time", _rippleTime);
	m_rippleShader->setUniform("in_Texture", m_mergeRt);
	m_rippleShader->draw(m_rippleRt);
}
