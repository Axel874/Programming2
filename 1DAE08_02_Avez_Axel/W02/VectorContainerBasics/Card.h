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

	explicit Card(Suit suit, int rank);
	explicit Card(int suit, int rank);

	~Card();

	void Draw(const Rectf& destRect) const;

	const Vector2f& GetDimensions() const;

	static const int minRank;
	static const int maxRank;
private:
	const Texture* m_pTexture;
	const Suit m_Suit;
	const int m_Rank;
	Vector2f m_Dimensions;
	std::string GetImagePath() const;
	void RetrieveDimensions();
	void LoadTexture();
	void DeleteTexture();
};