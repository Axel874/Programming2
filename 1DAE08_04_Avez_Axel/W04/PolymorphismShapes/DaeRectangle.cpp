#include "pch.h"		
#include "DaeRectangle.h"
#include "utils.h"

DaeRectangle::DaeRectangle( const Point2f &center, float width, float height, bool isFilled, const Color4f &color )
: DaeShape(width,height,center,isFilled,color)
{
}
void DaeRectangle::DrawFilled() const {
	utils::FillRect(Point2f{ m_Center.x - m_Width / 2,m_Center.y - m_Height / 2 }, m_Width, m_Height);
}
void DaeRectangle::DrawOutline() const {
	utils::DrawRect(Point2f{ m_Center.x - m_Width / 2,m_Center.y - m_Height / 2 }, m_Width, m_Height);
}