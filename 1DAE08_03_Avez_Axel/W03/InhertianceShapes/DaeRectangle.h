#pragma once
#include "DaeShape.h"

class DaeRectangle : public DaeShape
{
public:
	DaeRectangle( const Point2f& center, float width, float height, bool isFilled, const Color4f& color );
protected: 
	void DrawFilled() const;
	void DrawOutline() const;
};

 
