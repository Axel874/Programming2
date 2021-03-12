#include "pch.h"
#include "Camera.h"

Camera::Camera(float w, float h) : m_Dimensions(Vector2f{ w,h }), m_LevelBounds(Rectf{}){
}
Camera::Camera() : m_Dimensions(Vector2f{ 0,0 }), m_LevelBounds(Rectf{}){
}

void Camera::SetLevelBounds(const Rectf& r){
	m_LevelBounds = r;
}
void Camera::Draw(const Vector2f& target) const{
	utils::SetColor(Color4f(0, 0, 1, 1));
	Vector2f p = Clamp(Track(target));
	utils::DrawRect(p.ToPoint2f(), m_Dimensions.x, m_Dimensions.y);
}
void Camera::Transform(const Vector2f& target) const{
	Vector2f p = Clamp(Track(target));
	glTranslatef(-p.x,-p.y,0);
}

Vector2f Camera::Clamp(const Vector2f& camPos) const {
	Vector2f p = camPos;
	const Vector2f d = m_Dimensions;
	Vector2f lowBound{ m_LevelBounds.left,m_LevelBounds.bottom };
	Vector2f highBound = lowBound + Vector2f{ m_LevelBounds.width,m_LevelBounds.height };
	if (p.x < lowBound.x)p.x = lowBound.x;
	if ((p.x+d.x) > highBound.x)p.x = highBound.x-d.x;
	if (p.y < lowBound.y)p.y = lowBound.y;
	if ((p.y+d.y) > highBound.y)p.y = highBound.y-d.y;
	return p;
}
Vector2f Camera::Track(const Vector2f& target) const {
	Vector2f p{target};
	p -= m_Dimensions / 2.0f;
	return p;
}