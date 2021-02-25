#include "pch.h"
#include "Game.h"
#include "Texture.h"

Game::Game(const Window& window)
	:m_Window{ window }
{
	Initialize();
}
Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_Vertices.push_back(Point2f(-24, 0));
	m_Vertices.push_back(Point2f(0, -24));
	m_Vertices.push_back(Point2f(24, 0));
	m_Vertices.push_back(Point2f(0, 24));
	m_TransVertices = m_Vertices;

	m_pDiamond = new Texture("../resources/diamond.png");
}
void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_Q])m_Rotation += 60 * elapsedSec;
	if (state[SDL_SCANCODE_E])m_Rotation -= 60 * elapsedSec;
	if (state[SDL_SCANCODE_W])m_Translation.y += 120 * elapsedSec;
	if (state[SDL_SCANCODE_S])m_Translation.y -= 120 * elapsedSec;
	if (state[SDL_SCANCODE_A])m_Translation.x -= 120 * elapsedSec;
	if (state[SDL_SCANCODE_D])m_Translation.x += 120 * elapsedSec;

	Matrix2x3 tsr = Matrix2x3::CreateIdentityMatrix();
	Matrix2x3 t = Matrix2x3::CreateTranslationMatrix(m_Translation+m_Position);
	Matrix2x3 r = Matrix2x3::CreateRotationMatrix(m_Rotation);
	Matrix2x3 s = Matrix2x3::CreateScalingMatrix(m_Scale);

	tsr = tsr* t * s * r;
	m_TransVertices = tsr.Transform(m_Vertices);

}
void Game::Draw() const
{
	ClearBackground();
	if(m_Selected)utils::SetColor(Color4f(1, 0, 0, 1));
	else utils::SetColor(Color4f(0, 0, 1, 1));
	utils::DrawPolygon(m_TransVertices, true, 6);
	Rectf dstRect = Rectf(-24, -24, 48, 48);
	glPushMatrix();
		glTranslatef(m_Translation.x+m_Position.x, m_Translation.y+ m_Position.y, 0);
		glRotatef(m_Rotation,0, 0,1);
		glScalef(m_Scale, m_Scale, 1);
		m_pDiamond->Draw(dstRect);
	glPopMatrix();

	
	
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
}
void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
}
void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	
}
void Game::ProcessMouseWheelMotionEvent(const SDL_MouseWheelEvent& e) {
	float m = float(e.y);
	if (e.direction == SDL_MOUSEWHEEL_FLIPPED)m *= -1;
	m_Scale += m;
}
void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	if (e.button == SDL_BUTTON_LEFT) {
		Point2f p = Point2f{ float(e.x), float(m_Window.height - e.y) };
		if (utils::IsPointInPolygon(p, m_TransVertices)){
			m_Selected = !m_Selected;
		}
	}

}
void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::ClearBackground() const
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}
