#include "pch.h"
#include "Level.h"
#include "Texture.h"

Level::Level(){
	m_pBackgroundTexture = new Texture("../resources/images/background.png");
	m_pFenceTexture = new Texture("../resources/images/fence.png");

	m_FenceBottomLeft = Point2f{ 200,190 };

	m_Vertices.push_back(Point2f{ 0, 0 });
	m_Vertices.push_back(Point2f{0, 190 });
	m_Vertices.push_back(Point2f{ 340, 190 });
	m_Vertices.push_back(Point2f{ 408, 124 });
	m_Vertices.push_back(Point2f{ 560, 124});
	m_Vertices.push_back(Point2f{ 660, 224 });
	m_Vertices.push_back(Point2f{ 846,224 });
	m_Vertices.push_back(Point2f{ 846, 0 });
	m_Vertices.push_back(Point2f{ 0, 0 });
}
Level::~Level() {
	delete m_pBackgroundTexture;
	delete m_pFenceTexture;
}
void Level::DrawBackground()const{
	m_pBackgroundTexture->Draw();
}
void Level::DrawForeground()const{
	m_pFenceTexture->Draw(m_FenceBottomLeft);
}
void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const{
	Vector2f r1{ actorShape.left, actorShape.bottom };
	Vector2f r2{ r1 };
	r1 += Vector2f{ actorShape.width / 2.0f,actorShape.height };
	r2.x += actorShape.width / 2.0f;
	utils::HitInfo h;
	if (utils::Raycast(m_Vertices, r1.ToPoint2f(), r2.ToPoint2f(), h)) {
		actorShape.bottom = h.intersectPoint.y;
		actorVelocity.y = 0;
	}
}
bool Level::IsOnGround(const Rectf& actorShape)const{
	Vector2f r1{ actorShape.left, actorShape.bottom };
	Vector2f r2{ r1 };
	r1 += Vector2f{ actorShape.width / 2.0f,actorShape.height };
	r2.x += actorShape.width / 2.0f;
	r2.y -= 1;
	utils::HitInfo h;
	return utils::Raycast(m_Vertices, r1.ToPoint2f(), r2.ToPoint2f(), h);
}