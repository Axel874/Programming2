#pragma once
class Camera {
public:
	Camera(float w, float h);
	Camera();
	void SetLevelBounds(const Rectf& r);
	void Draw(const Vector2f& target) const;
	void Transform(const Vector2f& target) const;
private:
	Vector2f m_Dimensions;
	Rectf m_LevelBounds;

	Vector2f Clamp(const Vector2f& camPos) const;
	Vector2f Track(const Vector2f& target) const;

};