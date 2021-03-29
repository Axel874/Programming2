#include "pch.h"
#include "SpriteRenderer.h"
#include "Sprite.h"
#include "Camera.h"

SpriteRenderer::SpriteRenderer(std::vector<Sprite*>& managedSprites)
	: m_rSprites(managedSprites), m_Shader(ProgramShader("./resources/shaders/base"))
{
	//generate the VAO used to draw a single sprite
	GenerateVAO();
	//set the used texture unit to 0
	m_Shader.setInt("ourTexture", 0);
}
void SpriteRenderer::GenerateVAO()
{
	//create vertex array object and bind it
	glGenVertexArrays(1, &m_VAOHandle);
	glBindVertexArray(m_VAOHandle);
	//create data buffer
	GLuint VBO{};
	glGenBuffers(1, &VBO);
	//bind data buffer to vertex array object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//push vertex data to buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, Sprite::s_GLData, GL_DYNAMIC_DRAW);
	//set info about where to find 1st attribute of our data
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//idem for 2d attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//unbind the VAO
	glBindVertexArray(0);
}
SpriteRenderer::~SpriteRenderer() {
	for (Texture* t : m_LoadedTextures)delete t;
}

void SpriteRenderer::SetManagedSprites(std::vector<Sprite*>& sprites) { m_rSprites = sprites; }
void SpriteRenderer::RenderSprites(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, SDL_Window* window, const glm::vec3& camPos) {
	RenderSetup(viewMatrix, projectionMatrix);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawSprites(viewMatrix, camPos);
	SDL_GL_SwapWindow(window);
	 
	RenderCleanup();
}
void SpriteRenderer::RenderCleanup()
{
	//unbind shader
	m_Shader.UnBind();
	//unbind our sprite VAO
	glBindVertexArray(0);
}
void SpriteRenderer::RenderSetup(const glm::mat4& viewMatrix,const glm::mat4& projectionMatrix)
{
	//send shader our projection matrix
	m_Shader.setMatrix4fv("projection", projectionMatrix);
	//set our shader as the currently used shader by opengl
	m_Shader.Bind();
	//bind our "sprite data VAO"
	glBindVertexArray(m_VAOHandle);
}
void SpriteRenderer::DrawSprites(const glm::mat4& viewMatrix, const glm::vec3& camPos)
{
	//sort based on z index for proper alpha blending during render calls
	std::sort(m_rSprites.begin(), m_rSprites.end(), [](Sprite* a, Sprite* b) {return a->GetPosition().z < b->GetPosition().z; });
	for (Sprite* s : m_rSprites) {
		if (s->GetVisible()) { DrawSprite(s, viewMatrix, camPos); }
	}
}
void SpriteRenderer::DrawSprite(Sprite* s, const glm::mat4& viewMatrix, const glm::vec3& camPos)
{
	//get a pointer to the sprite's texture
	Texture* texture = GetTexture(s->GetTextureInfo().src);
	//tell texture unit 0 to use the sprite's texture
	texture->Bind(GL_TEXTURE0);
	//pass sprite model matrix to shader
	m_Shader.setMatrix4fv("model", s->GetModelMatrix());
	//adjust view matrix according to parralax factors
	glm::mat4 newViewMatrix = glm::translate(viewMatrix, glm::vec3(camPos.x * s->GetParallaxFactor().x, 0.0f, 0.0f));
	newViewMatrix = glm::translate(newViewMatrix, glm::vec3(0.0f, camPos.y * s->GetParallaxFactor().y, 0.0f));
	//pass adjusted view matrix to shader
	m_Shader.setMatrix4fv("view", newViewMatrix);
	//edit VBO based on UV coordinates supplied by sprite
	glBufferSubData(GL_ARRAY_BUFFER,0, sizeof(float) * 24, s->GetVBOData());
	//draw our sprite
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
Texture* SpriteRenderer::GetTexture(const std::string& src) {
	//first try to return a texture already loaded
	for (Texture* t : m_LoadedTextures) {
		if (t->GetSource() == src)return t;
	}
	//second if not found in loaded textures, load it and return it
	return LoadTexture(src);
}
Texture* SpriteRenderer::LoadTexture(const std::string& src) {
	m_LoadedTextures.push_back(new Texture(src, GL_RGBA));
	return m_LoadedTextures.back();
}