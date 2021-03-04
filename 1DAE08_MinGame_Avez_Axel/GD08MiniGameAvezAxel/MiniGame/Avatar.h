#pragma once
class Level;
class Avatar {
public:
	enum class ActionState {
		WAITING,
		MOVING,
		TRANSFORMING
	};

	Avatar();
	void Update(float dx, const Level& l);
	void UpdatePosition(float dx, const Level& l);
	void Draw() const;
	void PowerUpHit();
	Rectf GetShape() const;

private:
	static Vector2f dimensions;
	static Vector2f spawnLocation;
	static float horSpeed;
	static float jumpSpeed;
	static float gravity;
	static float transformDuration;
	
	Vector2f m_Position;
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
	ActionState m_ActionState;
	float m_AccuTransformSec;
	int m_PowerLevel;
};