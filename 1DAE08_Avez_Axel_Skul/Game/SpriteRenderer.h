#pragma once
#include "Texture.h"
#include "Sprite.h"
#include "ProgramShader.h"
class SpriteRenderer {
public:
	SpriteRenderer(std::vector<Sprite*>& managedSprites);
	~SpriteRenderer();

	void SetManagedSprites(std::vector<Sprite*>& sprites);
	void RenderSprites(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, SDL_Window* window );
	void RenderCleanup();
	void RenderSetup(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
private:
	static float s_SpriteData[24];

	ProgramShader m_Shader;
	std::vector<Sprite*>& m_rSprites;
	std::vector<Texture*> m_LoadedTextures;
	GLuint m_VAOHandle;
	
	Texture* GetTexture(const std::string& src);
	Texture* LoadTexture(const std::string& src);
	void DrawSprites();
	void DrawSprite(Sprite* s);
	void GenerateVAO();
};