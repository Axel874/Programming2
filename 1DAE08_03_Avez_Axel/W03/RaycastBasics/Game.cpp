#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
}
Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	InitSurface();
}
void Game::InitSurface()
{
	m_Surface.push_back(Point2f{ 50,50 });
	m_Surface.push_back(Point2f{ 50,400 });
	m_Surface.push_back(Point2f{ 425,450 });
	m_Surface.push_back(Point2f{ 800,400 });
	m_Surface.push_back(Point2f{ 800,50 });
	m_Surface.push_back(Point2f{ 425,25 });
}
void Game::Cleanup( )
{
}
void Game::Update( float elapsedSec )
{
}
void Game::Draw( ) const
{
	ClearBackground( );
	DrawSurface();
	DrawRay();
	utils::HitInfo h;
	if (utils::Raycast(m_Surface, m_RayStart, m_RayEnd, h)) {
		utils::DrawEllipse(h.intersectPoint, 5, 5, 3);
		utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
		utils::DrawLine(h.intersectPoint, (h.normal*30+Vector2f(h.intersectPoint)).ToPoint2f());
		Vector2f reflection{ m_RayStart,m_RayEnd };
		reflection *= 1 - h.lambda;
		reflection = reflection.Reflect(-h.normal);
		utils::DrawLine(h.intersectPoint, (Vector2f(h.intersectPoint) + reflection).ToPoint2f(), 5);
	}
	
}
void Game::DrawRay() const
{
	utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.0f));
	utils::DrawLine(m_RayStart, m_RayEnd, 3);
}
void Game::DrawSurface() const
{
	utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
	utils::FillPolygon(m_Surface);
	utils::SetColor(Color4f(1.f, 0.6f, 0.f, 1.f));
	utils::DrawPolygon(m_Surface, true, 5);
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
}
void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
}
void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	m_RayEnd.x = float(e.x);
	m_RayEnd.y = m_Window.height - float(e.y);
}
void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
}
void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ClearBackground( ) const
{
	glClearColor(180 / 255.0f, 180 / 255.0f, 180 / 255.0f, 1);
	glClear( GL_COLOR_BUFFER_BIT );
}
