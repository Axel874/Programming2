#include "pch.h"
#include "DataStructures.h"
//-----------------------------------------------------------------
// Rectf Constructors
//-----------------------------------------------------------------
Rectf::Rectf()
	:Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}
Rectf::Rectf(glm::vec2 position, glm::vec2 dimensions)
	: pos(position), dim(dimensions)
{}
Rectf::Rectf(float px, float py, float sx, float sy)
	: pos(glm::vec2(px, py)), dim(glm::vec2(sx,sy))
{}
glm::vec2 Rectf::GetMidpoint() const {return pos + (dim / 2.0f);}
//-----------------------------------------------------------------
// Circlef Constructors
//-----------------------------------------------------------------
Circlef::Circlef()
	:Circlef{ 0.0f, 0.0f, 0.0f }
{
}
Circlef::Circlef(float px, float py, float radius)
	: Circlef{ glm::vec2( px, py ), radius }
{}
Circlef::Circlef(const glm::vec2& center, float radius)
	: center{ center }, radius{ radius }
{}