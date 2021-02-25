#include "pch.h"
#include "Card.h"
#include "Texture.h"

const int Card::minRank{ 1 };
const int Card::maxRank{ 13 };
const float Card::rotationSpeed{ 180 };

Card::Card(int suit, int rank, float angle, const Circlef& c) : Card(Suit(suit), rank, angle,c) {}
Card::Card(Suit suit, int rank, float angle, const Circlef& c) : m_Suit(suit), m_Rank(rank), m_Angle(angle), m_Circle(c){
	LoadTexture();
	RetrieveDimensions();
}
void Card::RetrieveDimensions()
{
	m_Dimensions = Vector2f(m_pTexture->GetWidth(), m_pTexture->GetHeight());
}
void Card::LoadTexture()
{
	m_pTexture = new Texture(GetImagePath());
}

Card::~Card(){
	DeleteTexture();
}
void Card::DeleteTexture()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Card::Draw() const{
	const float rAngle = m_Angle * (3.1415f / 180);
	const Vector2f t = Vector2f{sinf(rAngle)*m_Circle.radius,cosf(rAngle) * m_Circle.radius } + Vector2f(m_Circle.center);

	glPushMatrix();
		glTranslatef(t.x, t.y, 0);
		//glRotatef(m_Angle, 0, 0, 1);
		m_pTexture->Draw(Point2f{-m_pTexture->GetWidth()/2.0f,-m_pTexture->GetHeight() / 2.0f });
	glPopMatrix();
}
void Card::Update(float dx) {
	m_Angle += dx * rotationSpeed;
}

std::string Card::GetImagePath() const { 
	return "../Resources/Cards/" + std::to_string(int(m_Suit) * 100 + m_Rank) + ".png";
}
const Vector2f& Card::GetDimensions() const { return m_Dimensions; }
