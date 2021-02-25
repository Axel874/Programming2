#include "pch.h"
#include "Game.h"
#include "Diamond.h"

Game::Game(const Window& window)
	:m_Window{ window }
{
	Initialize();
}
Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	for (int i = 0; i < 10; i++) {
		const Vector2f randPos{ float(utils::RandInt(0,int(m_Window.width))),
								float(utils::RandInt(0,int(m_Window.height))) };
		m_Diamonds.push_back(new Diamond{ randPos });
	}
}
void Game::Cleanup()
{
	for (Diamond*& d : m_Diamonds)delete d;
}

void Game::Update(float elapsedSec)
{
	for (Diamond* d : m_Diamonds)d->ProccessKeyboardState(SDL_GetKeyboardState(NULL), elapsedSec);
}
void Game::Draw() const
{
	ClearBackground();
	for (Diamond* d : m_Diamonds)d->Draw();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
}
void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
}
void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}
void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	for (Diamond* d : m_Diamonds)d->ProcessMouseDownEvent(e, m_Window);
}
void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}
void Game::ProcessMouseWheelEvent(const SDL_MouseWheelEvent& e) {
	for (Diamond* d : m_Diamonds)d->ProcessMouseWheelEvent(e);
}

void Game::ClearBackground() const
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}
