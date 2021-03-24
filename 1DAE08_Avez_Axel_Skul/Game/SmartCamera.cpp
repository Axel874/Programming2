#include "pch.h"
#include "SmartCamera.h"
#include "Sprite.h"
glm::vec3 SmartCamera::s_UpVector = glm::vec3(0.0f, 1.0f, 0.0f);//y = up
glm::vec3 SmartCamera::s_Direction = glm::vec3(0.0f, 0.0f, -1.0f);//facing negative axis
glm::vec3 SmartCamera::s_Dimensions = glm::vec3(500.0f, 280.0f, 10.0f);//ortho width/height/zClip

SmartCamera::SmartCamera(Sprite* target, float zPos, glm::vec2 xPadding, glm::vec2 yPadding)
	: Camera(glm::vec3(target->GetPosition()), s_Dimensions, s_UpVector, s_Direction), m_Target(target),
	m_XPadding(xPadding),m_YPadding(yPadding)
{
	m_Position.z = zPos;
}
void SmartCamera::Update(float dt) {
	const float minDeltaX = m_XPadding.x;
	const float maxDeltaX = m_Dimensions.x-m_XPadding.x;
	const float minDeltaY = m_YPadding.x;
	const float maxDeltaY = m_Dimensions.y-m_YPadding.y;

	const float deltaY = fabs(m_Target->GetPosition().y - m_Position.y);
	const float deltaX = fabs(m_Target->GetPosition().x - m_Position.x);

	if (deltaY < minDeltaY)m_Position.y = m_Target->GetPosition().y - minDeltaY;
	if (deltaY > maxDeltaY)m_Position.y = m_Target->GetPosition().y - maxDeltaY;
	if (deltaX < minDeltaX)m_Position.x = m_Target->GetPosition().x - minDeltaX;
	if (deltaX > maxDeltaX)m_Position.x = m_Target->GetPosition().x - maxDeltaX;
}