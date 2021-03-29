#pragma once
#include "Sprite.h"
class Player : public Sprite{
public:
	Player(const glm::vec3& position);
	~Player();

	void OnKeyDown(const SDL_KeyboardEvent& e) override;
	void OnOverlap(Sprite* const other) override;
	void OnHit(Sprite* const other, const HitDirection& direction) override;

	void Update(float dx) override;
private:
	//enum holds whether the sprite should be flipped while facing that direction
	enum class Direction {
		LEFT = true,
		RIGHT = false
	};
	static char s_TextureSource[64];
	static char s_AnimationsSource[64];
	static glm::vec2 s_Dimensions;
	static float s_JumpForce;
	static float s_Speed;
	static unsigned int s_MaxJumps;

	Direction m_CurrentDirection;
	glm::vec3 m_PreviousPosition;
	
	unsigned int m_JumpCount;
	unsigned int m_MaxJumps;


	void HandleKeyStates(float dx);
	void MoveX(float dx);
	void MoveY(float dy);
	void Jump();
	void SetDirection(Direction newDirection);
};