#include "pch.h"		
#include "DaeEllipse.h"
#include "utils.h"

DaeEllipse::DaeEllipse( const Point2f& center, float width, float height, const Color4f& color, bool isFilled )
	: DaeShape(width,height,center,isFilled,color)
{
}
void DaeEllipse::DrawFilled() const{
	utils::FillEllipse(m_Center, m_Width / 2, m_Height / 2);
}
void DaeEllipse::DrawOutline() const{
	utils::DrawEllipse(m_Center, m_Width / 2, m_Height / 2);
}
