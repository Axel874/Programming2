#include "pch.h"
#include "TrafficLight.h"

const Vector2f TrafficLight::dimensions{ 50,140 };
const Color4f TrafficLight::grey{ 180 / 255.0f, 180 / 255.0f, 180 / 255.0f, 1 };
const Vector2f TrafficLight::lightRadii{ 18.0f,18.0f };

TrafficLight::TrafficLight(const Vector2f& position)
	: m_Position(position) {
	m_State = State::OFF;
	m_AccumulatedSeconds = 0.0f;
}
TrafficLight::~TrafficLight() {}

void TrafficLight::Update(const float dx) {
	if (IsActive()) {
		m_AccumulatedSeconds += dx;

		switch (m_State)
		{
		case TrafficLight::State::GREEN:
			if (m_AccumulatedSeconds > 4) {
				SetState(State::ORANGE);
			}
			break;
		case TrafficLight::State::ORANGE:
			if (m_AccumulatedSeconds > 1) {
				SetState(State::RED);
			}
			break;
		case TrafficLight::State::RED:
			if (m_AccumulatedSeconds > 4) {
				SetState(State::GREEN);
			}
			break;
		}
	}

}
void TrafficLight::SetState(const State& state)
{
	m_State = state;
	m_AccumulatedSeconds = 0;
}
void TrafficLight::Draw() const {
	DrawSupport();
	DrawLights();
}
void TrafficLight::DrawSupport() const
{
	utils::SetColor(Color4f(0, 0, 0, 1));
	utils::FillRect(m_Position.ToPoint2f(), dimensions.x, dimensions.y);
}
void TrafficLight::DrawLights() const
{

	//red light position, should have carried an array of shapes but okay
	Vector2f p{ m_Position };
	p += Vector2f{ dimensions.x / 2.0f,dimensions.y / 6.0f * 5.0f };
	DrawLight(State::RED, Color4f(1, 0, 0, 1), p);
	p.y -= dimensions.y / 3.0f;
	DrawLight(State::ORANGE, Color4f(1, 0.5, 0, 1), p);
	p.y -= dimensions.y / 3.0f;
	DrawLight(State::GREEN, Color4f(0, 1, 0, 1), p);
}
void TrafficLight::DrawLight(
	const State& requiredState, const Color4f& lightColor, const Vector2f position) const
{
	if (m_State == requiredState)utils::SetColor(lightColor);
	else utils::SetColor(grey);
	utils::FillEllipse(position.ToPoint2f(), lightRadii.x, lightRadii.y);
}
void TrafficLight::ProcessMouseLeftClick(const Vector2f& pos) {
	bool isHit = false;
	Circlef c = Circlef(m_Position.ToPoint2f(), lightRadii.x);
	c.center.x += dimensions.x / 2.0f;
	c.center.y += dimensions.y / 6.0f * 5.0f;

	if (utils::IsPointInCircle(pos.ToPoint2f(), c)) {
		if (!IsActive())m_State = State::RED;
		isHit = true;
	}
	c.center.y -= dimensions.y / 3.0f;
	if (utils::IsPointInCircle(pos.ToPoint2f(), c)) {
		if (!IsActive())m_State = State::ORANGE;
		isHit = true;
	}
	c.center.y -= dimensions.y / 3.0f;
	if (utils::IsPointInCircle(pos.ToPoint2f(), c)) {
		if (!IsActive())m_State = State::GREEN;
		isHit = true;
	}

	if (IsActive() && !isHit) {
		Rectf r = Rectf(m_Position.x, m_Position.y, dimensions.x, dimensions.y);
		if (utils::IsPointInRect(pos.ToPoint2f(), r))SetState(State::OFF);
	}


}

bool TrafficLight::IsActive() const { return m_State != State::OFF; }
