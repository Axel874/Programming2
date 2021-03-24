#pragma once
#include "Sprite.h"
class SpriteAnimator {
public:
	SpriteAnimator(std::vector<Sprite*>& managedSprites);
	~SpriteAnimator();

	void UpdateAnimations(float dt);
	void SetManagedSprites(std::vector<Sprite*>& sprites);
private:
	std::vector<Sprite*>& m_rSprites;
};