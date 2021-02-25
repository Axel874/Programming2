#pragma once 
class Texture;
class Diamond {
public:
	explicit Diamond(const Vector2f pos);
	~Diamond();

	void Draw() const;
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e, const Window& w);
	void ProcessMouseWheelEvent(const SDL_MouseWheelEvent& e);
	void ProccessKeyboardState(const Uint8* s, const float dx);
private:
	static const Point2f vertices[4];
	static const Texture* pTexture;
	static int nrInstances;

	Vector2f m_Position;
	float m_Scale;
	float m_Rotation;
	Vector2f m_Translate;
	bool m_Selected;
};