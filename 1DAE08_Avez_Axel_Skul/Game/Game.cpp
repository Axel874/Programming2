#include "pch.h"
#include "Game.h"
#include "Sprite.h"
#include "SmartCamera.h"
#include "Player.h"
#include "Enemy.h"
//public
Game::Game() : m_Quitflag(false) {
	std::string src = "./resources/images/";

	//background sprite
	m_pSprites.push_back(new Sprite(src + "background/background.png", "", false, false, false, true, glm::vec3(0, -20, -3), glm::vec2(500,280),1.0f));
	m_pSprites.push_back(new Sprite(src + "background/background2.png", "", false, false, false, true, glm::vec3(0, -20, -2), glm::vec2(500, 140),1.0f));

	//floor hitbox + sprites
	m_pSprites.push_back(new Sprite("", "", false, false, true, false, glm::vec3(0, -20, 0), glm::vec2(32*30, 32)));
	for (int i = 0; i < 30; i++) {
		m_pSprites.push_back(new Sprite(src + "tiles/floor.png", "", false, false, false, true, glm::vec3(32*i, -20, 0), glm::vec2(32, 32)));
	}
	//enemies
	m_pSprites.push_back(new Enemy(glm::vec3(100, -20+32, -1.5)));
	m_pSprites.push_back(new Enemy(glm::vec3(150, -20+32, -1.5)));
	m_pSprites.push_back(new Enemy(glm::vec3(200, -20+32, -1.5)));
	//player
	m_pSprites.push_back(new Player(glm::vec3(30, -20 + 32, -1)));
	//camera
	m_pActiveCamera = new SmartCamera(m_pSprites.back(),5,glm::vec2(200),glm::vec2(32,100));
}
Game::~Game() {
	for (Sprite* s : m_pSprites)delete s;
	delete m_pActiveCamera;
}

void Game::Update(float deltaSeconds) {
	for (Sprite* s : m_pSprites) { s->Update(deltaSeconds); }
}

void Game::OnKeyDown(const SDL_KeyboardEvent& e) {
	for (Sprite* s : m_pSprites) { s->OnKeyDown(e); }
}
void Game::OnKeyUp(const SDL_KeyboardEvent& e) {
	for (Sprite* s : m_pSprites) { s->OnKeyUp(e); }
}

void Game::OnControllerAxisMotion(const SDL_ControllerAxisEvent& e) {
	for (Sprite* s : m_pSprites) { s->OnControllerAxisMotion(e); }
}
void Game::onControllerKeyDown(const SDL_ControllerButtonEvent& e) {
	for (Sprite* s : m_pSprites) { s->OnControllerKeyDown(e); }
}
void Game::onControllerKeyUp(const SDL_ControllerButtonEvent& e) {
	for (Sprite* s : m_pSprites) { s->OnControllerKeyUp(e); }
}

void Game::onMouseMotion(const SDL_MouseMotionEvent& e) {
	for (Sprite* s : m_pSprites) { s->OnMouseMotion(e); }
}
void Game::onMouseButtonDown(const SDL_MouseButtonEvent& e) {
	for (Sprite* s : m_pSprites) { s->OnMouseButtonDown(e); }
}
void Game::onMouseButtonUp(const SDL_MouseButtonEvent& e) {
	for (Sprite* s : m_pSprites) { s->OnMouseButtonUp(e); }
}
void Game::onMouseWheel(const SDL_MouseWheelEvent& e) {
	for (Sprite* s : m_pSprites) { s->OnMouseWheel(e); }
}

std::vector<Sprite*>& Game::GetSprites() { return m_pSprites; }
Camera* Game::GetActiveCamera() const { return m_pActiveCamera; }
bool Game::ShouldQuit() const { return m_Quitflag; }