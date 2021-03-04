#include "pch.h"
#include "Avatar.h"
#include "Level.h"

Vector2f Avatar::dimensions{36, 97 };
Vector2f Avatar::spawnLocation{ 50, 280};
float Avatar::horSpeed{ 200.0f };
float Avatar::jumpSpeed{ 600.0f };
float Avatar::gravity{ -981.0f };
float Avatar::transformDuration{ 1.0f };

Avatar::Avatar()
	: m_Velocity(Vector2f{ 0,0 }), m_Acceleration(Vector2f{ 0,gravity }),
	m_ActionState(ActionState::MOVING), m_AccuTransformSec(0.0f), m_PowerLevel(0),
	m_Position(spawnLocation)
{
}

void Avatar::Update(float dx, const Level& l){
	if (m_ActionState == ActionState::TRANSFORMING) {
		m_AccuTransformSec += dx;
		if (m_AccuTransformSec >= transformDuration) {
			m_ActionState = ActionState::WAITING;
		}
	}
	else {
		if (l.IsOnGround(GetShape())) {
			const Uint8* s = SDL_GetKeyboardState(NULL);
			bool recievedInput = false;
			if (s[SDL_SCANCODE_RIGHT]) {
				m_Position.x += dx * horSpeed;
				recievedInput = true;
			}
			if (s[SDL_SCANCODE_LEFT]) {
				m_Position.x -= dx * horSpeed;
				recievedInput = true;
			}
			if (s[SDL_SCANCODE_UP] || s[SDL_SCANCODE_SPACE]) {
				m_Velocity.y = jumpSpeed;
				m_Position.y += 5;
				recievedInput = true;
			}
			if (recievedInput){UpdatePosition(dx, l);}
			else { m_ActionState = ActionState::WAITING; }
		}
		else {
			UpdatePosition(dx, l);
		}

	}
}
void Avatar::UpdatePosition(float dx, const Level& l)
{
	Rectf s = GetShape();
	l.HandleCollision(s, m_Velocity);
	m_Position = Vector2f{ s.left,s.bottom };

	m_Velocity += m_Acceleration * dx;
	m_Position += m_Velocity*dx;

	m_ActionState = ActionState::MOVING;
}
void Avatar::Draw() const{
	const Rectf r = Rectf(m_Position.x, m_Position.y, dimensions.x, dimensions.y);
	if(m_ActionState == ActionState::WAITING)utils::SetColor(Color4f(1.0f, 1.0f, 0.0f, 1.0f));
	if(m_ActionState == ActionState::MOVING)utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	if(m_ActionState == ActionState::TRANSFORMING)utils::SetColor(Color4f(0.0f, 0.0f, 1.0f, 1.0f));
	utils::FillRect(r);

	utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 1.0f));
	Vector2f p{ m_Position + Vector2f{2,2 }};
	for (int i = 0; i < m_PowerLevel; i++) {
		utils::FillRect(p.ToPoint2f(), 4, 4);
		p.y += 6;
	}
}
void Avatar::PowerUpHit(){
	m_AccuTransformSec = 0;
	m_PowerLevel++;
	m_ActionState = ActionState::TRANSFORMING;
}
Rectf Avatar::GetShape() const{
	return Rectf(m_Position.x, m_Position.y, dimensions.x, dimensions.y);
}