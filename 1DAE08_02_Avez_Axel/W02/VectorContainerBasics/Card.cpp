#include "pch.h"
#include "Card.h"
#include "Texture.h"

const int Card::minRank{ 1 };
const int Card::maxRank{ 13 };

Card::Card(int suit, int rank) : Card(Suit(suit), rank) {}
Card::Card(Suit suit, int rank) : m_Suit(suit), m_Rank(rank){
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

void Card::Draw(const Rectf& destRect) const{
	m_pTexture->Draw(destRect);
}

std::string Card::GetImagePath() const { 
	return "../Resources/Cards/" + std::to_string(int(m_Suit) * 100 + m_Rank) + ".png";
}
const Vector2f& Card::GetDimensions() const { return m_Dimensions; }
