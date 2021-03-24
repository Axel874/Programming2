#pragma once
namespace CollissionUtils {
	struct HitInfo
	{
		float lambda;
		glm::vec2 intersectPoint;
		glm::vec2 normal;
	};
	bool IsPointInRect(const glm::vec2& p, const Rectf& r);
	bool IsPointInCircle(const glm::vec2& p, const Circlef& c);
	bool IsPointInPolygon(const glm::vec2& p, const std::vector<glm::vec2>& vertices);
	bool IsPointInPolygon(const glm::vec2& p, const glm::vec2* vertices, size_t nrVertices);

	bool IsOverlapping(const glm::vec2& a, const glm::vec2& b, const Circlef& c);
	bool IsOverlapping(const glm::vec2& a, const glm::vec2& b, const Rectf& r);

	bool IsOverlapping(const Rectf& r1, const Rectf& r2);
	bool IsOverlapping(const Rectf& r, const Circlef& c);
	bool IsOverlapping(const Circlef& c1, const Circlef& c2);
	bool IsOverlapping(const std::vector<glm::vec2>& vertices, const Circlef& c);
	bool IsOverlapping(const glm::vec2* vertices, size_t nrVertices, const Circlef& c);
	bool Raycast(const glm::vec2* vertices, const size_t nrVertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo);
	bool Raycast(const std::vector<glm::vec2>& vertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo);

	bool IntersectLineSegments(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& q1, const glm::vec2& q2, float& outLambda1, float& outLambda2, float epsilon = 1e-6);
	float DistPointLineSegment(const glm::vec2& p, const glm::vec2& a, const glm::vec2& b);
	bool IsPointOnLineSegment(const glm::vec2& p, const glm::vec2& a, const glm::vec2& b);
	bool IntersectRectLine(const Rectf& r, const glm::vec2& p1, const glm::vec2& p2, float& intersectMin, float& intersectMax);
}