#include "pch.h"
#include "DaeShape.h"

DaeShape::DaeShape(const float w, const float h, const Point2f& center,
	const bool isFilled, const Color4f& color)
	: m_Width(w), m_Height(h), m_Center(center), m_IsFilled(isFilled), m_Color(color)
{}
DaeShape::~DaeShape() {}
void DaeShape::Translate(const Vector2f& tr){
	m_Center += tr;
}
void DaeShape::Draw() const {
	utils::SetColor(m_Color);
	if (m_IsFilled)this->DrawFilled();
	else this->DrawOutline();
}

