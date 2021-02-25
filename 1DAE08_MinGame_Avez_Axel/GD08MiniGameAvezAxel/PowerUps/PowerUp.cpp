#include "pch.h"
#include "PowerUp.h"
#include "Texture.h"

const Texture* PowerUp::pTexture{ nullptr };
const float PowerUp::rotSpeed{ 360 };
int PowerUp::nrInstances{ 0 };

PowerUp::PowerUp(const Point2f& center, PowerUp::Type type) : m_Type(type), m_Angle(0) {
	if (nrInstances < 1) {
		pTexture = new Texture("../Resources/powerup.png");
	}
	m_Shape.center = center;
	m_Shape.radius = pTexture->GetWidth() / 2.0f;
	nrInstances++;
	if (type == Type::brown) {
		m_TextClip = Rectf(
			0.0f, pTexture->GetHeight(),
			pTexture->GetWidth(), pTexture->GetHeight() / 2.0f);
	}
	else {
		m_TextClip = Rectf(
			0.0f, pTexture->GetHeight() / 2.0f,
			pTexture->GetWidth(), pTexture->GetHeight() / 2.0f);
	}
}
PowerUp::~PowerUp() {
	if (nrInstances < 2) {
		delete pTexture;
		pTexture = nullptr;
	}
	nrInstances--;
}


void PowerUp::Update(float elapsedSec) {
	m_Angle += rotSpeed * elapsedSec;
}
void PowerUp::Draw() const {
	glPushMatrix();
	glTranslatef(m_Shape.center.x, m_Shape.center.y, 0);
	glRotatef(m_Angle, 0, 0, 1);
	pTexture->Draw(Point2f{ -pTexture->GetWidth() / 2.0f,-pTexture->GetWidth() / 2.0f }, m_TextClip);
	glPopMatrix();
}
bool PowerUp::IsOverlapping(const Rectf& rect) const {
	return utils::IsOverlapping(rect, m_Shape);
}