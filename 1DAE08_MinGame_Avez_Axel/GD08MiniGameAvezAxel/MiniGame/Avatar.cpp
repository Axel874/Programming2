#include "pch.h"
#include "Avatar.h"
#include "Level.h"
#include "Texture.h"

Vector2f Avatar::dimensions{71, 97 };
Vector2f Avatar::spawnLocation{ 50, 280};
float Avatar::horSpeed{ 200.0f };
float Avatar::jumpSpeed{ 600.0f };
float Avatar::gravity{ -981.0f };
float Avatar::transformDuration{ 1.0f };
Avatar::Animation Avatar::animation{
	nullptr,Vector2f{72.0f,97.0f},10,10,"..\\Resources\\Images\\avatarsheet.png"
};
int Avatar::nrInstances{ 0 };

Avatar::Avatar()
	: m_Velocity(Vector2f{ 0,0 }), m_Acceleration(Vector2f{ 0,gravity }),
	m_ActionState(ActionState::MOVING), m_AccuTransformSec(0.0f), m_PowerLevel(0),
	m_Position(spawnLocation), m_AnimationInfo(AnimationInfo{0,0})
{
	if (nrInstances == 0)animation.pTexture = new Texture(animation.source);
	nrInstances++;
}
Avatar::~Avatar(){
	nrInstances--;
	if (nrInstances == 0) delete animation.pTexture;
}

void Avatar::Update(float dx, const Level& l){
	if (m_ActionState == ActionState::TRANSFORMING) {
		m_AccuTransformSec += dx;
		if (m_AccuTransformSec >= transformDuration) {
			m_ActionState = ActionState::WAITING;
		}
	}
	else {
		handleKeyStates(dx, l);
		UpdatePosition(dx, l);
	}

	float& frameTime = m_AnimationInfo.frameTime;
	frameTime += dx;
	const float maxFrameTime = 1.0f/animation.framesPerSecond;
	const bool isTimeForNextFrame = frameTime > maxFrameTime;
	if(isTimeForNextFrame){
		m_AnimationInfo.frame++;
		m_AnimationInfo.frame %= (animation.nrFrames - 1);
		frameTime = 0;
	}
}
void Avatar::handleKeyStates(float dx, const Level& l)
{
	const Uint8* s = SDL_GetKeyboardState(NULL);
	bool recievedInput = false;
	m_Velocity.x = 0;
	if (s[SDL_SCANCODE_RIGHT]) {
		m_Velocity.x =  horSpeed;
		recievedInput = true;
	}
	if (s[SDL_SCANCODE_LEFT]) {
		m_Velocity.x = -horSpeed;
		recievedInput = true;
	}
	if ((s[SDL_SCANCODE_UP] || s[SDL_SCANCODE_SPACE]) && l.IsOnGround(GetShape())) {
		m_Velocity.y = jumpSpeed;
		m_Position.y += 5;
		recievedInput = true;
	}
	if (!recievedInput) { m_ActionState = ActionState::WAITING; }
	else { m_ActionState = ActionState::MOVING; }
}
void Avatar::UpdatePosition(float dx, const Level& l)
{
	m_Velocity += m_Acceleration * dx;
	m_Position += m_Velocity*dx;

	Rectf s = GetShape();
	l.HandleCollision(s, m_Velocity);
	m_Position = Vector2f{ s.left,s.bottom };
	if (m_Velocity.x != 0)m_ActionState = ActionState::MOVING;
}
void Avatar::Draw() const {


	float powerOffset = m_PowerLevel * animation.ClipDimensions.y * 3;
	int stateOffset = 1;
	if (m_ActionState == ActionState::MOVING) {
		stateOffset = 2;
	}
	if (m_ActionState == ActionState::TRANSFORMING) {
		stateOffset = 3;
		powerOffset = (m_PowerLevel - 1) * animation.ClipDimensions.y * 3;
	}


	const Rectf dstR = Rectf(0, 0, dimensions.x, dimensions.y);
	const Rectf srcR = Rectf(
		animation.ClipDimensions.x * m_AnimationInfo.frame, //xpos
		animation.ClipDimensions.y * stateOffset + powerOffset,//ypos
		animation.ClipDimensions.x, animation.ClipDimensions.y);//size

	glPushMatrix();
	if (m_Velocity.x < 0){
		glScalef(-1, 1, 1);
		glTranslatef(-m_Position.x-dimensions.x, m_Position.y, 0);
	}
	else {
		glTranslatef(m_Position.x, m_Position.y, 0);
	}
		animation.pTexture->Draw(dstR,srcR);
	glPopMatrix();
}
void Avatar::PowerUpHit(){
	m_AccuTransformSec = 0;
	m_PowerLevel++;
	m_ActionState = ActionState::TRANSFORMING;
}
Rectf Avatar::GetShape() const{
	return Rectf(m_Position.x, m_Position.y, dimensions.x, dimensions.y);
}