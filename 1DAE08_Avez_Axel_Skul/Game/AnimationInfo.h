#pragma once
struct Animation{
	std::string name;
	std::string fileName;
	unsigned int framesPerSecond;
	glm::vec2 frameDimensions;
	glm::vec2 firstFramePosition;
	float framePadding;
	unsigned int nrFrames;

	explicit Animation(
		const std::string& name,
		const std::string& fileName,
		unsigned int nrFrames,
		unsigned int framesPerSecond,
		const glm::vec2& frameDimensions,
		const glm::vec2& firstFramePosition,
		float framePadding
	);
	explicit Animation(
		const std::string& name,
		const std::string& fileName,
		unsigned int nrFrames,
		unsigned int framesPerSecond,
		float sx, float sy,
		float px, float py,
		float framePadding
	);
};
struct DataEntry {
	std::string id;
	std::string data;
};