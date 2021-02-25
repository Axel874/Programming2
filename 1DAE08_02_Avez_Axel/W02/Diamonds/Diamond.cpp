#include "pch.h"
#include "Diamond.h"
#include "Texture.h"

const Point2f Diamond::vertices[4]{ Point2f{-24,0},Point2f{0,-24},
									Point2f{24,0},Point2f{0,24} };
const Texture* Diamond::pTexture{ nullptr };
int Diamond::nrInstances{ 0 };

Diamond::Diamond(const Vector2f pos)
	: m_Rotation(0), m_Scale(1), m_Position(pos), m_Translate(Vector2f{}), m_Selected(false)
{
	if (nrInstances < 1)pTexture = new Texture("../Resources/Diamond.png");
	nrInstances++;

}
Diamond::~Diamond() {
	if (nrInstances < 2)delete pTexture;
	nrInstances--;
}

void Diamond::Draw() const {
	const Vector2f trans = m_Translate + m_Position;
	Matrix2x3 t = Matrix2x3::CreateIdentityMatrix() * Matrix2x3::CreateTranslationMatrix(trans);
	Matrix2x3 r = Matrix2x3::CreateRotationMatrix(m_Rotation);
	Matrix2x3 s = Matrix2x3::CreateScalingMatrix(m_Scale);
	Matrix2x3 trs = t * r * s;
	std::vector<Point2f> n = trs.Transform(std::vector<Point2f>(vertices, vertices + 4));

	if (m_Selected)utils::SetColor(Color4f(1, 0, 0, 1));
	else utils::SetColor(Color4f(0, 0, 1, 1));

	utils::DrawPolygon(n, true, 5.f);

	Rectf dstRect = Rectf(-24, -24, 48, 48);
	glPushMatrix();
	glTranslatef(trans.x,trans.y,0);
	glRotatef(m_Rotation, 0, 0, 1);
	glScalef(m_Scale,m_Scale,0);
	pTexture->Draw(dstRect);
	glPopMatrix();
}
void Diamond::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e, const Window& w) {
	const Point2f p{ float(e.x), float(w.height - e.y) };
	const Vector2f trans = m_Translate + m_Position;
	Matrix2x3 t = Matrix2x3::CreateIdentityMatrix() * Matrix2x3::CreateTranslationMatrix(trans);
	Matrix2x3 r = Matrix2x3::CreateRotationMatrix(m_Rotation);
	Matrix2x3 s = Matrix2x3::CreateScalingMatrix(m_Scale);
	Matrix2x3 trs = t * r * s;
	std::vector<Point2f> n = trs.Transform(std::vector<Point2f>(vertices, vertices + 4));
	if (utils::IsPointInPolygon(p, n))m_Selected = !m_Selected;
}
void Diamond::ProcessMouseWheelEvent(const SDL_MouseWheelEvent& e) {
	if (m_Selected) {
		float m = float(e.y);
		if (e.direction == SDL_MOUSEWHEEL_FLIPPED)m *= -1;
		m_Scale += m;
	}
}
void Diamond::ProccessKeyboardState(const Uint8* s, const float dx) {
	if (m_Selected) {
		if (s[SDL_SCANCODE_Q])m_Rotation += 60 * dx;
		if (s[SDL_SCANCODE_E])m_Rotation -= 60 * dx;
		if (s[SDL_SCANCODE_W])m_Translate.y += 120 * dx;
		if (s[SDL_SCANCODE_S])m_Translate.y -= 120 * dx;
		if (s[SDL_SCANCODE_A])m_Translate.x -= 120 * dx;
		if (s[SDL_SCANCODE_D])m_Translate.x += 120 * dx;
	}
}
