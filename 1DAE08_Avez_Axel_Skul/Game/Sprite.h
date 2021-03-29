#pragma once
#include "AnimationInfo.h"
class Sprite {
public:
	struct TextureInfo {
		std::string src; //path to source file
		//info about the region we want as our texture
		glm::vec2 position; //(0,0) -> (1,1)
		glm::vec2 dimensions; //(0,0) -> (1,1)

		explicit TextureInfo(const std::string& src, const glm::vec2& position, const glm::vec2& dimensions);
		explicit TextureInfo(const std::string& src);

	};

	enum class HitDirection {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	static float s_GLData[24];

	Sprite(
		const std::string& textureSrcPath, const std::string& animationsSrcPath,
		bool generatesOverlapEvents, bool simulatePhysics, bool blockOtherSprites,
		bool isVisible,const glm::vec3& position, const glm::vec2& scale,
		glm::vec2 parallaxFactor = glm::vec2(0.0f), const glm::vec3& rot = glm::vec3(0));
	virtual ~Sprite();

	virtual void Update(float deltaSeconds);

	virtual void OnKeyDown(const SDL_KeyboardEvent& e);
	virtual void OnKeyUp(const SDL_KeyboardEvent& e);

	virtual void OnControllerAxisMotion(const SDL_ControllerAxisEvent& e);
	virtual void OnControllerKeyDown(const SDL_ControllerButtonEvent& e);
	virtual void OnControllerKeyUp(const SDL_ControllerButtonEvent& e);

	virtual void OnMouseMotion(const SDL_MouseMotionEvent& e);
	virtual void OnMouseButtonDown(const SDL_MouseButtonEvent& e);
	virtual void OnMouseButtonUp(const SDL_MouseButtonEvent& e);
	virtual void OnMouseWheel(const SDL_MouseWheelEvent& e);

	virtual void OnOverlap(Sprite* const other);
	virtual void OnHit(Sprite* const other, const HitDirection& direction);

	TextureInfo GetTextureInfo() const;
	glm::mat4 GetModelMatrix() const;
	float* GetVBOData() const;
	bool GetGeneratesOverlapEvent()const;
	bool GetSimulatePhysics() const;
	bool GetIsAnimated() const;
	bool GetBLockOtherSprites() const;
	bool GetVisible() const;
	bool GetIsFlipped() const;
	Rectf GetBoundingBox() const;
	glm::vec3 GetPosition() const;
	glm::vec2 GetSize() const;
	glm::vec3 GetGravity() const;
	glm::vec3 GetVelocity() const;
	glm::vec3 GetAcceleration() const;
	Animation* GetCurrentAnimation() const;
	float GetTimeSinceFrameChange() const;
	glm::vec2 GetParallaxFactor() const;
	int GetCurrentFrame() const;

	void SetPosition(const glm::vec3& newPosition);
	void SetRotation(const glm::vec3& newRotation);
	void SetVelocity(const glm::vec3& newVelocity);
	void SetSize(const glm::vec2& newSize);
	void SetTextureInfo(const TextureInfo& newInfo);
	void SetTextureSource(const std::string& newSource);
	void SetTextureDimenions(const glm::vec2& newDimensions);
	void SetTexturePosition(const glm::vec2& newPosition);
	void SetTimeSinceFrameChange(float newTime);
	void SetCurrentFrame(int newFrame);
	void SetIsFlipped(bool flipped);
	void SetCurrentAnimation(const std::string& name);
protected:
	glm::vec3 m_Position;
	glm::vec2 m_Size;
	glm::vec3 m_Rotation;
	glm::vec3 m_Acceleration;
	glm::vec3 m_Velocity;
	glm::vec3 m_Gravity;
private:
	static glm::vec3 s_StandardGravity;
	bool m_SimulatePhysics;

	bool m_IsAnimated;
	std::vector<Animation> m_Animations;
	TextureInfo m_TextureInfo;
	float m_TimeSinceFrameChange;
	int m_CurrentFrame;
	Animation* m_CurrentAnimation;
	std::string m_AnimationsSourcePath;

	float* m_pVBOData;
	bool m_GeneratesOverlapevent;
	bool m_BlockOtherSprites;
	bool m_Visible;
	bool m_IsFlipped;
	glm::vec2 m_ParallaxFactor; //0 = remains still; 1 = moves with camera, individual control over x & y axis
	void UpdateVBO();
	std::string FindAnimationData(const std::vector<DataEntry>& dataEntries, const std::string& dataId);
	void LoadAnimations(const std::string& path);

};