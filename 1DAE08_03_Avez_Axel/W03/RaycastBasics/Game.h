#pragma once
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

	void DrawRay() const;

	void DrawSurface() const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	const Window m_Window;
	std::vector<Point2f> m_Surface;
	const Point2f m_RayStart{m_Window.width/2.0f, m_Window.height/2.0f};
	Point2f m_RayEnd;

	// FUNCTIONS
	void Initialize( );
	void InitSurface();
	void Cleanup( );
	void ClearBackground( ) const;
};