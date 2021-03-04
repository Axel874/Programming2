#pragma once
class DaeShape {
public:
	explicit DaeShape(const float w, const float h, const Point2f& center,
		const bool isFilled, const Color4f& color);
	virtual ~DaeShape();

	void Draw() const;
	void Translate(const Vector2f& tr);
protected:
	float m_Width;
	float m_Height;
	Point2f m_Center;
	bool m_IsFilled;
	Color4f m_Color;
private:
	virtual void DrawFilled() const = 0;
	virtual void DrawOutline() const = 0;
};