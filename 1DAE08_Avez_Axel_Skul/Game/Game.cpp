#include "pch.h"
#include "Game.h"
#include "Sprite.h"
#include "SmartCamera.h"
#include "Player.h"
//public
Game::Game() : m_Quitflag(false) {
	std::string src = "./resources/images/skul/tiles/floor.png";
	m_pSprites.push_back(new Sprite("./resources/images/skul/background/background.png", "", false, false, false, true, glm::vec3(0, 0, -2), glm::vec2(1920, 1080)));


	m_pSprites.push_back(new Sprite(src, "", false, false, true, false, glm::vec3(0, -20, 0), glm::vec2(32*10, 32)));
	for (int i = 0; i < 10; i++) {
		m_pSprites.push_back(new Sprite(src, "", false, false, false, true, glm::vec3(32*i, -20, 0), glm::vec2(32, 32)));
	}
	m_pSprites.push_back(new Player(glm::vec3(30, 1, -1)));
	m_pActiveCamera = new SmartCamera(m_pSprites.back(),5,glm::vec2(200),glm::vec2(50,100));
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