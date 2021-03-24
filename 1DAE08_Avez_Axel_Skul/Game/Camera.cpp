#include "pch.h"
#include "Camera.h"
//public
Camera::Camera(glm::vec3 position, glm::vec3 dimensions, glm::vec3 up, glm::vec3 direction)
	: m_Position(position),
	m_Up(up),
	m_Direction(direction),
	m_Dimensions(dimensions)
{
}

void Camera::Update(float deltaSeconds){}
glm::mat4 Camera::GetViewMatrix() const{
	return glm::lookAt(m_Position, m_Position+m_Direction, m_Up);
}
glm::mat4 Camera::GetProjectionMatrix() const{
	return glm::ortho(0.f, m_Dimensions.x, 0.f, m_Dimensions.y, 0.0f, m_Dimensions.z);
}
glm::vec3 Camera::GetPosition() const { return m_Position; }