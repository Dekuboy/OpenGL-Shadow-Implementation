#include "glm/glm.hpp"

class Camera
{
	glm::vec3 m_camPosition;
	glm::vec2 m_camAngle;
	float m_camSpeed;
public:
	Camera();
	Camera(glm::vec3 _camPosition,
		glm::vec2 _camAngle,
		float _camSpeed);
	~Camera();

	void update();

	void setPosition(glm::vec3 _position) { m_camPosition = _position; }
	void setAngle(glm::vec2 _angle) { m_camAngle = _angle; }
	void setSpeed(float _speed) { m_camSpeed = _speed; }
	glm::vec3 getPosition() { return m_camPosition; }
	glm::vec2 getAngle() { return m_camAngle; }
	float getSpeed() { return m_camSpeed; }
};