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
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
}
void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
}
void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
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
