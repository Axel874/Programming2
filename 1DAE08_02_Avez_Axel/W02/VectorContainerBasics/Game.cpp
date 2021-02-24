#include "pch.h"
#include "Game.h"
#include "Card.h"

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
	LoadCards();

}
void Game::LoadCards()
{
	for (int suit = 1; suit <= 4; suit++) {
		LoadSuit(suit);
	}
}
void Game::LoadSuit(const int suit)
{
	for (int rank = Card::minRank; rank <= Card::maxRank; rank++) {
		LoadCard(suit, rank);
	}
}
void Game::LoadCard(const int suit, int rank)
{
	m_Cards.push_back(new Card(suit, rank));

}

void Game::Cleanup()
{

	DeleteCards();
}
void Game::DeleteCards()
{
	for (Card*& c : m_Cards) {
		delete c;
	}
}

void Game::Update(float elapsedSec)
{

}
void Game::Draw() const
{
	ClearBackground();
	DrawCards();
}

void Game::DrawCards() const
{
	for (unsigned int row = 0; row < 4; row++) {
		DrawRow(row);
	}
}
void Game::DrawRow(unsigned int row) const
{
	for (unsigned int column = 0; column < 13; column++) {
		DrawCard(row, column);
	}
}
void Game::DrawCard(unsigned int row, unsigned int column) const
{
	const Card* const& c = m_Cards[row * 13 + column];
	const Vector2f d{ c->GetDimensions() * 0.5f };
	const Vector2f p{ d.x / 2.0f * column, m_Window.height - (d.y * (row + 1)) };
	const Rectf dstRect = Rectf(p.x, p.y, d.x, d.y);
	c->Draw(dstRect);
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
	for (int& i : m_Numbers) { i += increment; }
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
	if (isNotEmpty)m_Numbers.pop_back();
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
	std::cout << str << std::endl;
}
void Game::Print(const int& i)
{
	std::cout << i << " ";
}
