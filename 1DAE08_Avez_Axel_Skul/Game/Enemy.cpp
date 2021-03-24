#include "pch.h"
#include "Enemy.h"

char Enemy::s_AnimationsSource[64] = "./resources/images/tree enemy/animations.txt";
glm::vec2 Enemy::s_Dimensions = glm::vec2(50, 50);

Enemy::Enemy(const glm::vec3& position) 
	: Sprite("",s_AnimationsSource,false,false,false,true,position,s_Dimensions)
{

}