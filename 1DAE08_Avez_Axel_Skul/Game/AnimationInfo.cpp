#include "pch.h"
#include "AnimationInfo.h"
Animation::Animation(
	const std::string& name,
	const std::string& fileName,
	unsigned int nrFrames,
	unsigned int framesPerSecond,
	const glm::vec2& frameDimensions,
	const glm::vec2& firstFramePosition,
	float framePadding
)
	:name(name),
	fileName(fileName),
	nrFrames(nrFrames),
	framesPerSecond(framesPerSecond),
	frameDimensions(frameDimensions),
	firstFramePosition(firstFramePosition),
	framePadding(framePadding)
{}
Animation::Animation(
	const std::string& name,
	const std::string& fileName,
	unsigned int nrFrames,
	unsigned int framesPerSecond,
	float sx, float sy,
	float px, float py,
	float framePadding
): Animation(name,fileName,nrFrames,framesPerSecond,glm::vec2(sx,sy),glm::vec2(px,py),framePadding)
{}
