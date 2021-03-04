#pragma once
class Texture;
class PowerUp final
{
public:
	enum class Type 
	{  
		green = 1, 
		brown = 2	
	};
	explicit PowerUp(const Point2f& center, PowerUp::Type type );
	~PowerUp();
	void Update( float elapsedSec );
	void Draw( ) const;
	bool IsOverlapping(const Rectf& rect ) const;

private:
	static const Texture* pTexture;
	static const float rotSpeed;
	static int nrInstances;

	const Type m_Type;
	Rectf m_TextClip;
	Circlef m_Shape;
	float m_Angle;
};


