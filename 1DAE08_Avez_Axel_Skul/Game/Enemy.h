#pragma once
#include "Sprite.h"
class Enemy : public Sprite {
public:
	Enemy(const glm::vec3& position);
private:
	static char s_AnimationsSource[64];
	static glm::vec2 s_Dimensions;
};