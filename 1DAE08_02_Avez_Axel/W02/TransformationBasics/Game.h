#pragma once
class Texture;
class Game final
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseWheelMotionEvent(const SDL_MouseWheelEvent& e);

private:
	// DATA MEMBERS
	const Window m_Window;
	std::vector<Point2f> m_Vertices;
	std::vector<Point2f> m_TransVertices;
	float m_Scale = 1;
	float m_Rotation;
	Vector2f m_Translation;
	const Vector2f m_Position{24,24};
	bool m_Selected = false;
	Texture* m_pDiamond;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;
};