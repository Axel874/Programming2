#pragma once
class Texture;

class Card final
{
public:
	enum class Suit
	{
		clubs = 1,
		diamonds = 2,
		hearts = 3,
		spades = 4
	};

	explicit Card( Suit suit, int rank );
	~Card();
	void Draw( const Rectf& destRect ) const;

	static const int minRank;
	static const int maxRank;
	float GetWidth()const ;
	float GetHeight()const ;
private:
	float m_Width;
	float m_Height;
	const Texture *m_pTexture;
	const Suit m_Suit;
	const int m_Rank;
	std::string GetImagePath(Suit suit, int rank) const;
};