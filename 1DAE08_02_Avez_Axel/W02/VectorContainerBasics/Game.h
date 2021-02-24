#pragma once
class Card;
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

	void DrawCards() const;

	void DrawRow(unsigned int deck) const;

	void DrawCard(unsigned int deck, unsigned int rank) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );



private:
	// DATA MEMBERS
	const Window m_Window;
	std::vector<int> m_Numbers;
	std::vector<Card*> m_Cards;

	// FUNCTIONS
	void Initialize( );
	void LoadCards();
	void LoadSuit(int suit);
	void LoadCard(int suit, int rank);
	void Cleanup( );

	void DeleteCards();

	void ClearBackground( ) const;
	void RemoveElement();
	void AddElement();
	void PrintElements();
	void PrintLn(const std::string& str);
	void Print(const int& i);
	void IncrementElements(const int& increment);
	void ShuffelCards(const int shuffleCount);
	void ShuffleCard();
};