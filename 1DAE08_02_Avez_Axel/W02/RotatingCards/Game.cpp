#include "pch.h"
#include "Game.h"
#include "Card.h"

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
	for (int i = 0; i < 13; i++) {
		m_Cards.push_back(new Card(3,i+1,i*(360/13.0f),Circlef(m_Window.width/2.0f, m_Window.height / 2.0f, m_Window.height / 4.0f)));
	}
}
void Game::Cleanup( )
{
	for (Card* c : m_Cards) {
		delete c;
	}
}

void Game::Update( float elapsedSec )
{
	for (Card* c : m_Cards) {
		c->Update(elapsedSec);
	}
}
void Game::Draw( ) const
{
	ClearBackground( );
	for (Card* c : m_Cards) {
		 c->Draw();
	}
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
	glClearColor(0,0,0, 1);
	glClear( GL_COLOR_BUFFER_BIT );
}
