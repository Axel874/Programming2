#include "pch.h"
#include "OverlapTester.h"
#include "CollissionUtils.h"

OverlapTester::OverlapTester(std::vector<Sprite*>& managedSprites):m_rSprites(managedSprites){}
OverlapTester::~OverlapTester(){}

void OverlapTester::TestOverlap(){
	std::vector<Sprite*> spritesToTest;
	//extract sprites that trigger overlaps
	for (Sprite* s : m_rSprites) {
		if (s->GetGeneratesOverlapEvent()) { spritesToTest.push_back(s); }
	}
	//loop over all sprites
	for (Sprite* s1 : spritesToTest) {
		//loop over all sprites again
		for (Sprite* s2 : spritesToTest) {
			//if its another sprite
			if (s1 != s2 ) {
				//if overlapping call overlap function inside sprite
				if (CollissionUtils::IsOverlapping(s1->GetBoundingBox(),s2->GetBoundingBox())) {
					s1->OnOverlap(s2);
				}
			}
		}
	}
}
void OverlapTester::SetManagedSprites(std::vector<Sprite*>& sprites) { m_rSprites = sprites; }
