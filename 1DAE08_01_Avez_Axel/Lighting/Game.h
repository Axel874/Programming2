#pragma once
struct Vector2f;
struct Point2f;
class Game
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void ProcessKeyboardState(float elapsedSec);
	void MovePlatform(float elapsedSec);
	void UpdateSurfaceNormal();
	void Draw( ) const;

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
	Point2f* m_SurfaceRight;
	Point2f* m_SurfaceLeft;
	Vector2f* m_SurfaceNormal;
	float m_MovementSpeed;
	

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void TestVector2fStruct();
};