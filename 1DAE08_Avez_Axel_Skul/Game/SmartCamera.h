#pragma once
#include "Camera.h"
class Sprite;
class SmartCamera : public Camera {
public:
	static glm::vec3 s_UpVector;
	static glm::vec3 s_Direction;
	static glm::vec3 s_Dimensions;

	SmartCamera(Sprite* target, float zPos, glm::vec2 xPadding, glm::vec2 yPadding);

	void Update(float dt) override;
private:
	Sprite* m_Target;
	glm::vec2 m_XPadding; //x = left padding, y = right padding
	glm::vec2 m_YPadding; //x = bottom padding, y = top padding
};