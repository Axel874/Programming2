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

	explicit Card(Suit suit, int rank, float angle, const Circlef& circle);
	explicit Card(int suit, int rank, float angle, const Circlef& circle);

	~Card();

	void Draw() const;
	void Update(float dx);

	const Vector2f& GetDimensions() const;

	static const int minRank;
	static const int maxRank;
private:
	static const float rotationSpeed;

	const Texture* m_pTexture;
	const Suit m_Suit;
	const int m_Rank;
	float m_Angle;
	Circlef m_Circle;
	Vector2f m_Dimensions;
	std::string GetImagePath() const;
	void RetrieveDimensions();
	void LoadTexture();
	void DeleteTexture();
};