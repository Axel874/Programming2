#include "pch.h"
#include "Game.h"
#include "TrafficLight.h"

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
	m_Padding = 5;

	GenerateTrafficLights();
}
void Game::GenerateTrafficLights()
{
	GenerateTrafficLightRow();
}

void Game::GenerateTrafficLightRow()
{
	Vector2f p{ m_Padding, m_Window.height - m_Padding - TrafficLight::dimensions.y };
	for (int i = 0; i < 5; i++) {
		m_TrafficLights.push_back(new TrafficLight(p));
		p.x += TrafficLight::dimensions.x + m_Padding;
	}
}

void Game::Cleanup( )
{
	DeleteTrafficLights();
	
}
void Game::DeleteTrafficLights()
{
	for (TrafficLight*& t : m_TrafficLights) {
		delete t;
		t = nullptr;
	}
}

void Game::Update( float elapsedSec )
{
	UpdateTrafficLights(elapsedSec);
}
void Game::UpdateTrafficLights(float elapsedSec)
{
	for (TrafficLight*& t : m_TrafficLights) {
		t->Update(elapsedSec);
	}
}
void Game::Draw( ) const
{
	ClearBackground( );
	DrawTrafficLights();
}
void Game::DrawTrafficLights() const
{
	for (TrafficLight* const& t : m_TrafficLights)t->Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}
void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}
void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}
void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	for (TrafficLight*& t : m_TrafficLights) {
		t->ProcessMouseLeftClick(Vector2f(float(e.x), float(m_Window.height - e.y)));
	}
}
void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor(180 / 255.0f, 180 / 255.0f, 180 / 255.0f, 1);
	glClear( GL_COLOR_BUFFER_BIT );
}
