#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(glm::vec3 _camPosition, glm::vec2 _camAngle, float _camSpeed) :
	m_camPosition(_camPosition), m_camAngle(_camAngle), m_camSpeed(_camSpeed)
{}

Camera::~Camera()
{

}

void Camera::update()
{

}
