#include "pch.h"
#include "Sprite.h"

//public//
//vertex/uv data for drawing a basic sprite in opengl
float Sprite::s_GLData[24] = {
	// positions      // tex coords 
	//x       y        u      v
	0.0f,    0.0f,    0.0f,  0.0f,	//bottom left
	1.0f,    1.0f,    1.0f,  1.0f,	//top right
	0.0f,    1.0f,    0.0f,  1.0f,	//top left

	0.0f,    0.0f,    0.0f,  0.0f,	//bottom left
	1.0f,    1.0f,    1.0f,  1.0f,	//top right
	1.0f,    0.0f,    1.0f,  0.0f,	//bottom right
};
glm::vec3 Sprite::s_StandardGravity = glm::vec3(0, -981.0f, 0);

Sprite::TextureInfo::TextureInfo(const std::string& src, const glm::vec2& position, const glm::vec2& dimensions)
	: src(src), dimensions(dimensions), position(position) {}
Sprite::TextureInfo::TextureInfo(const std::string& src)
	: TextureInfo(src, glm::vec2(0), glm::vec2(1)) {}

Sprite::Sprite(
	const std::string& srcPath, const std::string& animationsSrcPath,
	bool generatesOverlapEvents, bool simulatePhysics, bool blockOtherSprites,
	bool isVisible, const glm::vec3& position, const glm::vec2& scale,
	float parallaxFactor,const glm::vec3& rot)
	: m_Size(scale), m_TextureInfo(TextureInfo(srcPath)), m_Position(position),
	m_Rotation(rot), m_GeneratesOverlapevent(generatesOverlapEvents), m_Visible(isVisible),
	m_SimulatePhysics(simulatePhysics), m_BlockOtherSprites(blockOtherSprites), m_ParallaxFactor(parallaxFactor)
{
	m_TimeSinceFrameChange = 0;
	m_CurrentFrame = 0;
	m_Acceleration = glm::vec3(0);//start with 0 acceleration
	m_Velocity = glm::vec3(0);//start with 0 velocity
	m_Gravity = s_StandardGravity;//use standard gravity
	m_pVBOData = new float[24]; //create array for vbo data
	m_IsFlipped = false;
	UpdateVBO(); //update vbo data to match texture uv info
	if (!animationsSrcPath.empty()) {
		LoadAnimations(animationsSrcPath); //load animations' data into m_animations
		m_AnimationsSourcePath = animationsSrcPath.substr(0, animationsSrcPath.find_last_of("\/")) + "/";
		SetCurrentAnimation(m_Animations[0].name);
		m_IsAnimated = true;
	}
	else { m_IsAnimated = false; }
}
Sprite::~Sprite() {
	delete[] m_pVBOData;
}

void Sprite::Update(float deltaSeconds) {}

void Sprite::OnKeyDown(const SDL_KeyboardEvent& e) {}
void Sprite::OnKeyUp(const SDL_KeyboardEvent& e) {}

void Sprite::OnControllerAxisMotion(const SDL_ControllerAxisEvent& e) {}
void Sprite::OnControllerKeyDown(const SDL_ControllerButtonEvent& e) {}
void Sprite::OnControllerKeyUp(const SDL_ControllerButtonEvent& e) {}

void Sprite::OnMouseMotion(const SDL_MouseMotionEvent& e) {}
void Sprite::OnMouseButtonDown(const SDL_MouseButtonEvent& e) {}
void Sprite::OnMouseButtonUp(const SDL_MouseButtonEvent& e) {}
void Sprite::OnMouseWheel(const SDL_MouseWheelEvent& e) {}

void Sprite::OnOverlap(Sprite* const other) {}
void Sprite::OnHit(Sprite* const other, const HitDirection& direction) {}

void Sprite::SetTextureInfo(const TextureInfo& newInfo) { m_TextureInfo = newInfo; UpdateVBO(); }
void Sprite::SetTextureSource(const std::string& newSource) { m_TextureInfo.src = newSource; }
void Sprite::SetTextureDimenions(const glm::vec2& newDimensions) { m_TextureInfo.dimensions = newDimensions; UpdateVBO(); }
void Sprite::SetTexturePosition(const glm::vec2& newPosition) { m_TextureInfo.position = newPosition; UpdateVBO(); }
void Sprite::SetPosition(const glm::vec3& newPosition) {
	m_Position = newPosition;
}
void Sprite::SetRotation(const glm::vec3& newRotation) { m_Rotation = newRotation; }
void Sprite::SetSize(const glm::vec2& newSize) { m_Size = newSize; }
void Sprite::SetIsFlipped(bool flipped) { m_IsFlipped = flipped; }
void Sprite::SetVelocity(const glm::vec3& newVelocity) { m_Velocity = newVelocity; }
void Sprite::SetTimeSinceFrameChange(float newTime) { m_TimeSinceFrameChange = newTime; }
void Sprite::SetCurrentFrame(int newFrame) { m_CurrentFrame = newFrame; }
void Sprite::SetCurrentAnimation(const std::string& name) {
	for (Animation& a : m_Animations) {
		if (a.name == name) {
			m_CurrentAnimation = &a;
			SetTextureDimenions(a.frameDimensions);
			m_TimeSinceFrameChange = 1.0f / a.framesPerSecond;
			m_CurrentFrame = 0;
			SetTextureSource( m_AnimationsSourcePath + m_Animations[0].fileName);
			return;
		}
	}
	std::cout << "can't find animation '" << name << "'" << std::endl;
}


Sprite::TextureInfo Sprite::GetTextureInfo() const { return m_TextureInfo; }
float* Sprite::GetVBOData() const { return m_pVBOData; }
glm::mat4 Sprite::GetModelMatrix() const {
	//calculate model matrix//

	//calculate half size
	const glm::vec2 halfSize = m_Size / 2.0f;
	//start with identity matrix
	glm::mat4 model = glm::mat4(1.0f);
	//matrix multiplications from bottom to top !
	//apply transform to correct for sprite flipping
	if (m_IsFlipped) { model = glm::translate(model, glm::vec3(m_Size.x, 0, 0)); }
	//apply translation matrix (5)
	model = glm::translate(model, m_Position);
	//reverse transform done to rotate around midpoint (4)
	model = glm::translate(model, glm::vec3(halfSize, 1));
	//apply rotations (3)
	model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	//offset model matrix to rotate around midpoint (2)
	model = glm::translate(model, glm::vec3(-halfSize, 1));
	//apply negative scale if flipped (1)
	if (m_IsFlipped) { model = glm::scale(model, glm::vec3(-m_Size.x, m_Size.y, 1)); }
	else { model = glm::scale(model, glm::vec3(m_Size.x, m_Size.y, 1)); }

	return model;
}
bool Sprite::GetGeneratesOverlapEvent()const { return m_GeneratesOverlapevent; }
bool Sprite::GetSimulatePhysics()const { return m_SimulatePhysics; }
bool Sprite::GetIsAnimated()const { return m_IsAnimated; }
bool Sprite::GetBLockOtherSprites()const { return m_BlockOtherSprites; }
bool Sprite::GetVisible()const { return m_Visible; }
bool Sprite::GetIsFlipped()const { return m_IsFlipped; }
Animation* Sprite::GetCurrentAnimation() const { return m_CurrentAnimation; }
Rectf Sprite::GetBoundingBox() const {
	Rectf box = Rectf(m_Position, m_Size);
	return box;
}
glm::vec3 Sprite::GetPosition() const { return m_Position; }
glm::vec2 Sprite::GetSize() const { return m_Size; }
glm::vec3 Sprite::GetGravity() const { return m_Gravity; }
glm::vec3 Sprite::GetVelocity() const { return m_Velocity; }
glm::vec3 Sprite::GetAcceleration()  const { return m_Acceleration; }
float Sprite::GetTimeSinceFrameChange() const { return m_TimeSinceFrameChange; }
float Sprite::GetParallaxFactor() const { return m_ParallaxFactor; }
int Sprite::GetCurrentFrame() const { return m_CurrentFrame; }


//private
void Sprite::UpdateVBO()
{
	//update VBO uv data
	const glm::vec2& d = m_TextureInfo.dimensions;
	const glm::vec2& p = m_TextureInfo.position;
	float data[24] = {
		// positions      // tex coords 
		//x       y        u		   v
		0.0f,    0.0f,    p.x,         p.y,	        //bottom left
		1.0f,    1.0f,    p.x + d.x,   p.y + d.y,	//top right
		0.0f,    1.0f,    p.x,		   p.y + d.y,	//top left

		0.0f,    0.0f,    p.x,         p.y,	        //bottom left
		1.0f,    1.0f,    p.x + d.x,   p.y + d.y,	//top right
		1.0f,    0.0f,    p.x + d.x,   p.y,	        //bottom right
	};
	std::copy(data, data + 24, m_pVBOData);
}
std::string Sprite::FindAnimationData(const std::vector<DataEntry>& dataEntries, const std::string& dataId) {
	for (DataEntry entry : dataEntries) {
		if (entry.id == dataId) { return entry.data; }
	}
	std::cout << "failed to find animation data '" << dataId << "'" << std::endl;
	return "";
}
void Sprite::LoadAnimations(const std::string& path) {
	std::string line;
	std::ifstream file(path);
	std::vector<DataEntry> dataEntries;
	while (std::getline(file, line)) {
		DataEntry rawData;
		rawData.id = line.substr(0, line.find(":"));
		rawData.data = line.substr(line.find(":") + 1, line.length());
		dataEntries.push_back(rawData);
		//every 8 entries, extract them and put them into an animation struct->push to our animations list->reset entries
		if (dataEntries.size() == 9) {
			Animation animation = Animation(
				FindAnimationData(dataEntries, "name"),
				FindAnimationData(dataEntries, "filesource"),
				std::stoi(FindAnimationData(dataEntries, "nrFrames")),
				std::stoi(FindAnimationData(dataEntries, "framesPerSecond")),
				std::stof(FindAnimationData(dataEntries, "frameSizeX")),
				std::stof(FindAnimationData(dataEntries, "frameSizeY")),
				std::stof(FindAnimationData(dataEntries, "startOffsetX")),
				std::stof(FindAnimationData(dataEntries, "startOffsetY")),
				std::stof(FindAnimationData(dataEntries, "framePadding"))
			);
			m_Animations.push_back(animation);
			dataEntries.clear();
		}
	}
}
