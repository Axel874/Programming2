#include "pch.h"
#include "SpriteAnimator.h"

SpriteAnimator::SpriteAnimator(std::vector<Sprite*>& managedSprites): m_rSprites(managedSprites){}
SpriteAnimator::~SpriteAnimator(){}

void SpriteAnimator::UpdateAnimations(float dt){
	for (Sprite* s : m_rSprites) {
		if (s->GetIsAnimated()) {
			s->SetTimeSinceFrameChange(s->GetTimeSinceFrameChange() + dt);
			Animation* animation = s->GetCurrentAnimation();
			if (s->GetTimeSinceFrameChange() > (1.0f / animation->framesPerSecond)) {
				s->SetTimeSinceFrameChange(0);//reset acumulator
				s->SetCurrentFrame(s->GetCurrentFrame() + 1); //track next frame
				s->SetCurrentFrame(s->GetCurrentFrame() % animation->nrFrames); //loop back to first frame if past nrframes
				//start position + (one frame and padding) * (frames played)
				const float posX = animation->firstFramePosition.x + ((animation->frameDimensions.x + animation->framePadding) * s->GetCurrentFrame());
				s->SetTexturePosition(glm::vec2(posX, animation->firstFramePosition.y));
			}
		}
	}
}
void SpriteAnimator::SetManagedSprites(std::vector<Sprite*>& sprites){}