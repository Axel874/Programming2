#pragma once
#include "Sprite.h"
class PhysicsEngine {
public:
	PhysicsEngine(std::vector<Sprite*>& managedSprites);
	~PhysicsEngine();

	void UpdateSprites(float dt);
	void UpdatePosition(Sprite* sprite, float dt);
	void UpdateVelocity(Sprite* sprite, float dt);
	bool CheckTopCollission(Sprite* sprite, Sprite* other);
	bool CheckLeftCollission(Sprite* sprite, Sprite* other);
	bool CheckRightCollission(Sprite* sprite, Sprite* other);
	bool CheckBottomCollission(Sprite* sprite, Sprite* other);
	void SetManagedSprites(std::vector<Sprite*>& sprites);
private:
	std::vector<Sprite*>& m_rSprites;
};