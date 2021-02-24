#include "pch.h"
#include "Game.h"

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

}
void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{

}
void Game::Draw() const
{
	ClearBackground();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	const SDL_Keycode key = e.keysym.sym;
	if (key == SDLK_KP_PLUS) {
		AddElement();
		PrintElements();
	}
	else if (key == SDLK_KP_MINUS) {
		RemoveElement();
		PrintElements();
	}
	else if (key == SDLK_UP) {
		IncrementElements(1);
		PrintElements();
	}
	else if (key == SDLK_DOWN) {
		IncrementElements(-1);
		PrintElements();
	}

}
void Game::IncrementElements(const int& increment)
{
	for (int& i : m_Numbers) { i+=increment; }
}
void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{

}
void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}
void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}
void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{

}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Game::RemoveElement()
{
	const bool isNotEmpty = !m_Numbers.empty();
	if(isNotEmpty)m_Numbers.pop_back();
}
void Game::AddElement()
{
	m_Numbers.push_back(utils::RandInt(0, 30));
}
void Game::PrintElements()
{
	//for (unsigned int i = 0; i < m_Numbers.size(); i++) {
	//	Print(m_Numbers[i]);
	//}
	for (const int& i : m_Numbers) { Print(i); }
	PrintLn("");
}
void Game::PrintLn(const std::string& str)
{
	std::cout << str <<  std::endl;
}
void Game::Print(const int& i)
{
	std::cout << i << " ";
}
