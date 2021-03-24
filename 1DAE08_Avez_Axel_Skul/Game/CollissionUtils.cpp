#include "pch.h"
#include "CollissionUtils.h"

bool CollissionUtils::IsPointInRect(const glm::vec2& p, const Rectf& r)
{
	return (p.x >= r.pos.x &&
		p.x <= r.pos.x + r.dim.x &&
		p.y >= r.pos.y &&
		p.y <= r.pos.y + r.dim.y);
}
bool CollissionUtils::IsPointInCircle(const glm::vec2& p, const Circlef& c)
{
	float squaredDist{ (p.x - c.center.x) * (p.x - c.center.x) + (p.y - c.center.y) * (p.y - c.center.y) };
	float squaredRadius{ c.radius * c.radius };
	return (squaredRadius >= squaredDist);
}
bool CollissionUtils::IsPointInPolygon(const glm::vec2& p, const std::vector<glm::vec2>& vertices)
{
	return IsPointInPolygon(p, vertices.data(), vertices.size());
}
bool CollissionUtils::IsPointInPolygon(const glm::vec2& p, const glm::vec2* vertices, size_t nrVertices)
{
	if (nrVertices < 2)
	{
		return false;
	}
	// 1. First do a simple test with axis aligned bounding box around the polygon
	float xMin{ vertices[0].x };
	float xMax{ vertices[0].x };
	float yMin{ vertices[0].y };
	float yMax{ vertices[0].y };
	for (size_t idx{ 1 }; idx < nrVertices; ++idx)
	{
		if (xMin > vertices[idx].x)
		{
			xMin = vertices[idx].x;
		}
		if (xMax < vertices[idx].x)
		{
			xMax = vertices[idx].x;
		}
		if (yMin > vertices[idx].y)
		{
			yMin = vertices[idx].y;
		}
		if (yMax < vertices[idx].y)
		{
			yMax = vertices[idx].y;
		}
	}
	if (p.x < xMin || p.x > xMax || p.y < yMin || p.y > yMax)
	{
		return false;
	}

	// 2. Draw a virtual ray from anywhere outside the polygon to the point 
	//    and count how often it hits any side of the polygon. 
	//    If the number of hits is even, it's outside of the polygon, if it's odd, it's inside.
	int numberOfIntersectionPoints{ 0 };
	glm::vec2 p2{ xMax + 10.0f, p.y }; // Horizontal line from point to point outside polygon (p2)

	// Count the number of intersection points
	float lambda1{}, lambda2{};
	for (size_t i{ 0 }; i < nrVertices; ++i)
	{
		if (IntersectLineSegments(vertices[i], vertices[(i + 1) % nrVertices], p, p2, lambda1, lambda2))
		{
			if (lambda1 > 0 && lambda1 <= 1 && lambda2 > 0 && lambda2 <= 1)
			{
				++numberOfIntersectionPoints;
			}
		}
	}
	if (numberOfIntersectionPoints % 2 == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CollissionUtils::IsOverlapping(const glm::vec2& a, const glm::vec2& b, const Rectf& r)
{
	// if one of the line segment end points is in the rect
	if (CollissionUtils::IsPointInRect(a, r) || CollissionUtils::IsPointInRect(b, r))
	{
		return true;
	}

	HitInfo hitInfo{};
	glm::vec2 vertices[]{ glm::vec2 {r.pos.x, r.pos.y},
		glm::vec2{ r.pos.x + r.dim.x, r.pos.y },
		glm::vec2{ r.pos.x + r.dim.x, r.pos.y + r.dim.y },
		glm::vec2{ r.pos.x, r.pos.y + r.dim.y } };

	return Raycast(vertices, 4, a, b, hitInfo);
}
bool CollissionUtils::IsOverlapping(const Rectf& r1, const Rectf& r2)
{
	// If one rectangle is on left side of the other
	if ((r1.pos.x + r1.dim.x) < r2.pos.x || (r2.pos.x + r2.dim.x) < r1.pos.x)
	{
		return false;
	}

	// If one rectangle is under the other
	if (r1.pos.y > (r2.pos.y + r2.dim.y) || r2.pos.y > (r1.pos.y + r1.dim.y))
	{
		return false;
	}

	return true;
}
bool CollissionUtils::IsOverlapping(const Rectf& r, const Circlef& c)
{
	// Is center of circle in the rectangle?
	if (IsPointInRect(c.center, r))
	{
		return true;
	}
	// Check line segments
	if (CollissionUtils::DistPointLineSegment(c.center, glm::vec2{ r.pos.x, r.pos.y }, glm::vec2{ r.pos.x, r.pos.y + r.dim.y }) <= c.radius)
	{
		return true;
	}
	if (CollissionUtils::DistPointLineSegment(c.center, glm::vec2{ r.pos.x, r.pos.y }, glm::vec2{ r.pos.x + r.dim.x, r.pos.y }) <= c.radius)
	{
		return true;
	}
	if (CollissionUtils::DistPointLineSegment(c.center, glm::vec2{ r.pos.x + r.dim.x, r.pos.y + r.dim.y }, glm::vec2{ r.pos.x, r.pos.y + r.dim.y }) <= c.radius)
	{
		return true;
	}
	if (CollissionUtils::DistPointLineSegment(c.center, glm::vec2{ r.pos.x + r.dim.x, r.pos.y + r.dim.y }, glm::vec2{ r.pos.x + r.dim.x, r.pos.y }) <= c.radius)
	{
		return true;
	}
	return false;
}
bool CollissionUtils::IsOverlapping(const Circlef& c1, const Circlef& c2)
{
	// squared distance between centers
	float xDistance{ c1.center.x - c2.center.x };
	float yDistance{ c1.center.y - c2.center.y };
	float squaredDistance{ xDistance * xDistance + yDistance * yDistance };

	float squaredTouchingDistance{ (c1.radius + c2.radius) * (c1.radius + c2.radius) };
	return (squaredDistance < squaredTouchingDistance);
}
bool CollissionUtils::IsOverlapping(const glm::vec2& a, const glm::vec2& b, const Circlef& c)
{
	return CollissionUtils::DistPointLineSegment(c.center, a, b) <= c.radius;
}
bool CollissionUtils::IsOverlapping(const std::vector<glm::vec2>& vertices, const Circlef& c)
{
	return IsOverlapping(vertices.data(), vertices.size(), c);
}
bool CollissionUtils::IsOverlapping(const glm::vec2* vertices, size_t nrVertices, const Circlef& c)
{
	// Verify whether one of vertices is in circle
	for (size_t i{ 0 }; i < nrVertices; ++i)
	{
		if (IsPointInCircle(vertices[i], c))
		{
			return true;
		}
	}

	// Verify whether one of the polygon edges overlaps with circle
	for (size_t i{ 0 }; i < nrVertices; ++i)
	{
		if (DistPointLineSegment(c.center, vertices[i], vertices[(i + 1) % nrVertices]) <= c.radius)
		{
			return true;
		}
	}

	// No overlapping with edges, verify whether circle is completely inside the polygon
	if (IsPointInPolygon(c.center, vertices, nrVertices))
	{
		return true;
	}
	return false;
}

bool CollissionUtils::IntersectLineSegments(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& q1, const glm::vec2& q2, float& outLambda1, float& outLambda2, float epsilon)
{
	bool intersecting{ false };

	glm::vec2 p1p2{ p2-p1 };
	glm::vec2 q1q2{ q2-q1 };

	// Cross product to determine if parallel
	float denom = glm::cross(glm::vec3(p1p2,0), glm::vec3(q1q2,0)).z;

	// Don't divide by zero
	if (std::abs(denom) > epsilon)
	{
		intersecting = true;

		glm::vec2 p1q1{ q1-p1 };

		float num1 = glm::cross(glm::vec3(p1q1, 0), glm::vec3(q1q2, 0)).z;
		float num2 = glm::cross(glm::vec3(p1q1, 0), glm::vec3(p1p2, 0)).z;
		outLambda1 = num1 / denom;
		outLambda2 = num2 / denom;
	}
	else // are parallel
	{
		// Connect start points
		glm::vec2 p1q1{ q1-p1 };

		// Cross product to determine if segments and the line connecting their start points are parallel, 
		// if so, than they are on a line
		// if not, then there is no intersection
		if (std::abs(glm::cross(glm::vec3(p1q1, 0), glm::vec3(q1q2, 0)).z) > epsilon)
		{
			return false;
		}

		// Check the 4 conditions
		outLambda1 = 0;
		outLambda2 = 0;
		if (CollissionUtils::IsPointOnLineSegment(p1, q1, q2) ||
			CollissionUtils::IsPointOnLineSegment(p2, q1, q2) ||
			CollissionUtils::IsPointOnLineSegment(q1, p1, p2) ||
			CollissionUtils::IsPointOnLineSegment(q2, p1, p2))
		{
			intersecting = true;
		}
	}
	return intersecting;
}
bool CollissionUtils::Raycast(const std::vector<glm::vec2>& vertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo)
{
	return Raycast(vertices.data(), vertices.size(), rayP1, rayP2, hitInfo);
}
bool CollissionUtils::Raycast(const glm::vec2* vertices, const size_t nrVertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo)
{
	if (nrVertices == 0)
	{
		return false;
	}

	std::vector<HitInfo> hits;

	Rectf r1, r2;
	// r1: minimal AABB rect enclosing the ray
	r1.pos.x = std::min(rayP1.x, rayP2.x);
	r1.pos.y = std::min(rayP1.y, rayP2.y);
	r1.dim.x = std::max(rayP1.x, rayP2.x) - r1.pos.x;
	r1.dim.y = std::max(rayP1.y, rayP2.y) - r1.pos.y;

	// Line-line intersections.
	for (size_t idx{ 0 }; idx <= nrVertices; ++idx)
	{
		// Consider line segment between 2 consecutive vertices
		// (modulo to allow closed polygon, last - first vertice)
		glm::vec2 q1 = vertices[(idx + 0) % nrVertices];
		glm::vec2 q2 = vertices[(idx + 1) % nrVertices];

		// r2: minimal AABB rect enclosing the 2 vertices
		r2.pos.x = std::min(q1.x, q2.x);
		r2.pos.y = std::min(q1.y, q2.y);
		r2.dim.x = std::max(q1.x, q2.x) - r2.pos.x;
		r2.dim.y = std::max(q1.y, q2.y) - r2.pos.y;

		if (IsOverlapping(r1, r2))
		{
			float lambda1{};
			float lambda2{};
			if (IntersectLineSegments(rayP1, rayP2, q1, q2, lambda1, lambda2))
			{
				if (lambda1 > 0 && lambda1 <= 1 && lambda2 > 0 && lambda2 <= 1)
				{
					HitInfo linesHitInfo{};
					linesHitInfo.lambda = lambda1;
					linesHitInfo.intersectPoint = glm::vec2{ rayP1.x + ((rayP2.x - rayP1.x) * lambda1), rayP1.y + ((rayP2.y - rayP1.y) * lambda1) };
					glm::vec2 q1q2 = glm::vec2(q2 - q1);
					glm::vec2 orthogonal = glm::vec2(-q1q2.y, q1q2.x);
					linesHitInfo.normal = glm::normalize(orthogonal);
					hits.push_back(linesHitInfo);
				}
			}
		}
	}

	if (hits.size() == 0)
	{
		return false;
	}

	// Get closest intersection point and copy it into the hitInfo parameter
	hitInfo = *std::min_element
	(
		hits.begin(), hits.end(),
		[](const HitInfo& first, const HitInfo& last)
		{
			return first.lambda < last.lambda;
		}
	);
	return true;
}

bool  CollissionUtils::IsPointOnLineSegment(const glm::vec2& p, const glm::vec2& a, const glm::vec2& b)
{
	glm::vec2 ap{ p-a }, bp{ p-b };
	// If not on same line, return false
	
	if (abs(glm::cross(glm::vec3(ap, 0), glm::vec3(bp, 0)).z) > 0.001f)
	{
		return false;
	}

	// Both vectors must point in opposite directions if p is between a and b
	if (glm::dot(ap,bp) > 0)
	{
		return false;
	}

	return true;
}
float  CollissionUtils::DistPointLineSegment(const glm::vec2& p, const glm::vec2& a, const glm::vec2& b)
{
	glm::vec2 ab{ b-a };
	glm::vec2 ap{ p-a };
	glm::vec2 abNorm{ glm::normalize(ab) };
	float distToA{ glm::dot(abNorm,ap) };

	// If distToA is negative, then the closest point is A
	// return the distance a, p
	if (distToA < 0)
	{
		return glm::length(ap);
	}
	// If distToA is > than dist(a,b) then the closest point is B
	// return the distance b, p
	float distAB{ glm::length(ab) };
	if (distToA > distAB)
	{
		return glm::length(glm::vec2{ p-b });
	}

	// Closest point is between A and B, calc intersection point
	glm::vec2 intersection{ glm::dot(abNorm,ap) * abNorm + glm::vec2{ a } };
	return glm::length(glm::vec2{ p - intersection });
}
bool CollissionUtils::IntersectRectLine(const Rectf& r, const glm::vec2& p1, const glm::vec2& p2, float& intersectMin, float& intersectMax)
{
	// Parameters
	// input: 
	//   r: axis aligned bounding box, start and end points of line segment.
	//   p1, p2: line
	// output: 
	//   intersectMin and intersectMax: in the interval [0,1] if intersection point is on the line segment. 
	// return
	//   true if there is an intersection

	// Example of how to use
	//float min{};
	//float max{};
	//if (CollissionUtils::IntersectRectLine(rect, p1, p2, min, max))
	//{
	//	glm::vec2 intersectP1{ p1 + (glm::vec2(p2) - glm::vec2(p1)) * min };
	//	glm::vec2 intersectP2{ p1 + (glm::vec2(p2) - glm::vec2(p1)) * max };
	//}

	// 4 floats to convert rect space to line space
	// x1: value between 0 and 1 where 0 is on p1 and 1 is on p2, <0 and >1 means intersection is not on line segment
	float x1{ (r.pos.x - p1.x) / (p2.x - p1.x) };
	float x2{ (r.pos.x + r.dim.x - p1.x) / (p2.x - p1.x) };
	float y1{ (r.pos.y - p1.y) / (p2.y - p1.y) };
	float y2{ (r.pos.y + r.dim.y - p1.y) / (p2.y - p1.y) };

	using std::max; using std::min;
	float tMin{ max(min(x1,x2),min(y1,y2)) };
	float tMax{ min(max(x1,x2), max(y1,y2)) };
	if (tMin > tMax)
	{
		return false;
	}
	intersectMin = tMin;
	intersectMax = tMax;
	return true;
}