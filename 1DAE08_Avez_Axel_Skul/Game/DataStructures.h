#pragma once
struct Rectf
{
	Rectf();
	explicit Rectf(float px, float py, float sx, float sy);
	explicit Rectf(glm::vec2 position,glm::vec2 dimensions);

	glm::vec2 pos;
	glm::vec2 dim;

	glm::vec2 GetMidpoint() const;
};
struct Circlef
{
	Circlef();
	explicit Circlef(const glm::vec2& center, float radius);
	explicit Circlef(float px, float py, float radius);

	glm::vec2 center;
	float radius;
};