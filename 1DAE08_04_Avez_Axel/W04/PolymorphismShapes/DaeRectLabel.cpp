#include "pch.h"		
#include "DaeRectLabel.h"
#include "Texture.h"

DaeRectLabel::DaeRectLabel( const Point2f& center, float width, float height,bool isFilled, const Color4f& color, const std::string& label, const Color4f& textColor, TTF_Font* pFont )
	: DaeRectangle(center,width,height,isFilled,color)
, m_pLabelText{ new Texture(label, pFont, textColor) }
{
	m_MarginX = ( m_Width - m_pLabelText->GetWidth( ) ) / 2;
	m_MarginY = ( m_Height - m_pLabelText->GetHeight( ) ) / 2;
}

DaeRectLabel::~DaeRectLabel( )
{
	delete m_pLabelText;
	m_pLabelText = nullptr;
}

void DaeRectLabel::DrawFilled( ) const
{
	DaeRectangle::DrawFilled();
	DrawLabel();
}
void DaeRectLabel::DrawOutline()const {
	DaeRectangle::DrawOutline();
	DrawLabel();
}
void DaeRectLabel::DrawLabel() const
{
	// Label
	Point2f bottomLeft{ m_Center.x - m_Width / 2 + m_MarginX, m_Center.y - m_Height / 2 + m_MarginY };
	m_pLabelText->Draw(bottomLeft);
}

