#pragma once
#include "Sprite.h"
class OverlapTester {
public:
	OverlapTester(std::vector<Sprite*>& managedSprites);
	~OverlapTester();

	void TestOverlap();
	void SetManagedSprites(std::vector<Sprite*>& sprites);
private:
	std::vector<Sprite*>& m_rSprites;
};