#pragma once
class Level;
class Texture;

class Avatar {
public:
	enum class ActionState {
		WAITING,
		MOVING,
		TRANSFORMING
	};

	struct Animation {
		Texture* pTexture;
		Vector2f ClipDimensions;
		int nrFrames;
		int framesPerSecond;
		char source[64];
	};

	struct AnimationInfo {
		int frame;
		float frameTime;
	};

	Avatar();
	~Avatar();
	void Update(float dx, const Level& l);
	void handleKeyStates(float dx, const Level& l);
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
	static Animation animation;
	static int nrInstances;

	Vector2f m_Position;
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
	ActionState m_ActionState;
	AnimationInfo m_AnimationInfo;
	float m_AccuTransformSec;
	int m_PowerLevel;
};