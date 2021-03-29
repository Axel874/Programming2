#include "pch.h"
#include "Player.h"

char Player::s_AnimationsSource[64] = "./resources/images/skul/animations.txt";
glm::vec2 Player::s_Dimensions = glm::vec2(50, 50);
float Player::s_JumpForce = 400.0f;
float Player::s_Speed = 200.0f;
unsigned int Player::s_MaxJumps = 2;

//public
Player::Player(const glm::vec3& position)
	: Sprite("", s_AnimationsSource, true, true, false, true, position, s_Dimensions),
	m_CurrentDirection(Direction::RIGHT), m_JumpCount(0), m_MaxJumps(s_MaxJumps), m_PreviousPosition(position) {}
Player::~Player() {}

void Player::OnKeyDown(const SDL_KeyboardEvent& e) {
	switch (e.keysym.scancode) {
	case SDL_SCANCODE_SPACE: {Jump(); break; }
	}
}
void Player::OnOverlap(Sprite* const other) {}
void Player::OnHit(Sprite* const other, const HitDirection& direction) {
	switch (direction)
	{
	case Sprite::HitDirection::UP:
		break;
	case Sprite::HitDirection::DOWN:
		m_JumpCount = 0;
		break;
	case Sprite::HitDirection::LEFT:
		break;
	case Sprite::HitDirection::RIGHT:
		break;
	default:
		break;
	}
}

void Player::Update(float dt) {
	HandleKeyStates(dt);
	//determine animation based comparing prev position to new position
	if (m_Position.x > m_PreviousPosition.x) { SetDirection(Direction::RIGHT); }
	else if (m_Position.x < m_PreviousPosition.x) { SetDirection(Direction::LEFT); }

	if (m_Position.x != m_PreviousPosition.x) { SetCurrentAnimation("running"); }
	else { SetCurrentAnimation("idle"); }
	//set prev psoition to new position
	m_PreviousPosition = m_Position;
}

//private
void Player::HandleKeyStates(float dt) {
	const Uint8* s = SDL_GetKeyboardState(NULL);
	bool isMoving = false;
	if (s[SDL_SCANCODE_D]) { MoveX(s_Speed * dt);}
	if (s[SDL_SCANCODE_A]) { MoveX(-s_Speed * dt);}

}
void Player::MoveX(float dx) {
	m_Position.x += dx;
}
void Player::MoveY(float dx) {
	m_Position.y += dx;
}
void Player::Jump()
{
	if (m_JumpCount < m_MaxJumps) {
		Sprite::m_Velocity.y = s_JumpForce;
		++m_JumpCount;
	}

}
void Player::SetDirection(Direction newDirection) {
	m_CurrentDirection = newDirection;
	SetIsFlipped(bool(m_CurrentDirection));
}
