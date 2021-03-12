#pragma once
#include "DaeRectangle.h"

class Texture;
class DaeRectLabel : public DaeRectangle
{
public:
	DaeRectLabel( const Point2f& center, float width, float height, bool isFilled, const Color4f& color, const std::string& label, const Color4f& textColor, TTF_Font* pFont );
	~DaeRectLabel( );
private:
	Texture* m_pLabelText;
	float m_MarginX;
	float m_MarginY;

	void DrawFilled() const override;
	void DrawLabel() const;
	void DrawOutline() const override;
};

 
