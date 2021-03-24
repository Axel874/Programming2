#include "pch.h"
#include "PhysicsEngine.h"
#include "CollissionUtils.h"

PhysicsEngine::PhysicsEngine(std::vector<Sprite*>& managedSprites) :m_rSprites(managedSprites) {}
PhysicsEngine::~PhysicsEngine() {}

void PhysicsEngine::UpdateSprites(float dt) {
	for (Sprite* sprite : m_rSprites) {
		//if sprite has to simulate physics
		if (sprite->GetSimulatePhysics()) {
			UpdateVelocity(sprite, dt);////apply acceleration
			UpdatePosition(sprite, dt);////apply velocity to position
			//for every sprite that blocks phsyics objects, check if we are affected
			bool horColTrig = false;
			bool vertColTrig= false;
			for (Sprite* other : m_rSprites) {
				//if not ourselves, and the other sprite blocks us see if we are colliding into the other sprite
				if (sprite != other && other->GetBLockOtherSprites()) {
					//only check for vertical collissions if we have not vertically collided yet to improve performance
					if (!vertColTrig) { vertColTrig = CheckBottomCollission(sprite, other); }
					if (!vertColTrig) { vertColTrig = CheckTopCollission(sprite, other); }
					//only check for horizontal collissions if we have not vertically collided yet to improve performance
					if (!horColTrig) { horColTrig = CheckRightCollission(sprite, other); }
					if (!horColTrig) { horColTrig = CheckLeftCollission(sprite, other); }
				}
				//if we have collided on x and y axis, stop checking for collissions to improve performance
				if (horColTrig && vertColTrig) { break; };
			}
		}
	}
}
void PhysicsEngine::UpdatePosition(Sprite* sprite, float dt)
{
	const glm::vec3 deltaPosition = sprite->GetVelocity() * dt;
	sprite->SetPosition(sprite->GetPosition() + deltaPosition);
}
void PhysicsEngine::UpdateVelocity(Sprite* sprite, float dt)
{
	const glm::vec3 deltaVelocity = (sprite->GetAcceleration() + sprite->GetGravity()) * dt;
	sprite->SetVelocity(sprite->GetVelocity() + deltaVelocity);
}
bool PhysicsEngine::CheckTopCollission(Sprite* sprite, Sprite* other)
{
	const Rectf ourRect = sprite->GetBoundingBox();
	const Rectf otherRect = other->GetBoundingBox();
	const glm::vec2 mP = ourRect.GetMidpoint();
	const glm::vec2 uP = mP + glm::vec2(0, ourRect.dim.y / 2.0f);//up point
	glm::vec2 p1 = otherRect.pos; //bottom left point
	glm::vec2 p2 = otherRect.pos + glm::vec2(otherRect.dim.x, 0); //bottom right point
																  //extend the collission platform to account for the sprite's width (minus a little not to overlap right/left colission)
	p1.x -= ((ourRect.dim.x / 2.0f) - 5.0f);
	p2.x += ((ourRect.dim.x / 2.0f) - 5.0f);

	float hitInfo1, hitInfo2;
	const bool linesIntersect = CollissionUtils::IntersectLineSegments(mP, uP, p1, p2, hitInfo1, hitInfo2);
	//if lines intersect and hitinfo1 (y intersect point) / hitInfo2 (x intersect point) are between 0 and 1
	if (linesIntersect && hitInfo1 > 0 && hitInfo1 < 1 && hitInfo2 > 0 && hitInfo2 < 1) {
		glm::vec3 p = sprite->GetPosition(); //get old position
		p.y = p1.y - ourRect.dim.y; //set y value to bottom of platform - our height
		sprite->SetVelocity(sprite->GetVelocity() * glm::vec3(1, 0, 1));//eliminate y velocity when hitting the ground
		sprite->SetPosition(p);//set new position to sprite
		sprite->OnHit(other, Sprite::HitDirection::UP);
		return true;
	}
	return false;
}
bool PhysicsEngine::CheckBottomCollission(Sprite* sprite, Sprite* other)
{
	const Rectf otherRect = other->GetBoundingBox();
	const Rectf ourRect = sprite->GetBoundingBox();
	const glm::vec2 mP = ourRect.GetMidpoint();
	const glm::vec2 dP = mP - glm::vec2(0, ourRect.dim.y / 2.0f);//down point
	glm::vec2 p1 = otherRect.pos + glm::vec2(0, otherRect.dim.y); //top left point
	glm::vec2 p2 = otherRect.pos + otherRect.dim; //top right point
	//extend the collission platform to account for the sprite's width (minus a little not to overlap right/left colission)
	p1.x -= ((ourRect.dim.x / 2.0f) - 5.0f);
	p2.x += ((ourRect.dim.x / 2.0f) - 5.0f);

	float hitInfo1, hitInfo2;
	const bool linesIntersect = CollissionUtils::IntersectLineSegments(mP, dP, p1, p2, hitInfo1, hitInfo2);
	//if lines intersect and hitinfo1 (y intersect point) / hitInfo2 (x intersect point) are between 0 and 1
	if (linesIntersect && hitInfo1 > 0 && hitInfo1 < 1 && hitInfo2 > 0 && hitInfo2 < 1) {
		glm::vec3 p = sprite->GetPosition(); //get old position
		p.y = p1.y; //set y value to top of platform
		sprite->SetVelocity(sprite->GetVelocity() * glm::vec3(1, 0, 1));//eliminate y velocity when hitting the ground
		sprite->SetPosition(p);//set new position to sprite
		sprite->OnHit(other, Sprite::HitDirection::DOWN);
		return true;
	}
	return false;
}
bool PhysicsEngine::CheckLeftCollission(Sprite* sprite, Sprite* other)
{
	const Rectf otherRect = other->GetBoundingBox();
	const Rectf ourRect = sprite->GetBoundingBox();
	const glm::vec2 mP = ourRect.GetMidpoint();
	const glm::vec2 lP = mP - glm::vec2(ourRect.dim.x / 2.0f, 0);//left point
	glm::vec2 p1 = otherRect.pos + glm::vec2(otherRect.dim.x, 0); //bottom right point
	glm::vec2 p2 = otherRect.pos + otherRect.dim; //top right point
	//extend the collission platform to account for the sprite's height (minus a little not to overlap top/bottom collission)
	p1.y -= ((ourRect.dim.y / 2.0f) - 5.0f);
	p2.y += ((ourRect.dim.y / 2.0f) - 5.0f);
	float hitInfo1, hitInfo2;
	const bool linesIntersect = CollissionUtils::IntersectLineSegments(mP, lP, p1, p2, hitInfo1, hitInfo2);
	//if lines intersect and hitinfo1 (y intersect point) / hitInfo2 (x intersect point) are between 0 and 1
	if (linesIntersect && hitInfo1 > 0 && hitInfo1 < 1 && hitInfo2 > 0 && hitInfo2 < 1) {
		glm::vec3 p = sprite->GetPosition(); //get old position
		p.x = p1.x; //set x value to left of platform 
		sprite->SetVelocity(sprite->GetVelocity() * glm::vec3(0, 1, 1));//eliminate x velocity when hitting the wall
		sprite->SetPosition(p);//set new position to sprite
		sprite->OnHit(other, Sprite::HitDirection::LEFT);
		return true;
	}
	return false;
}
bool PhysicsEngine::CheckRightCollission(Sprite* sprite, Sprite* other)
{
	const Rectf otherRect = other->GetBoundingBox();
	const Rectf ourRect = sprite->GetBoundingBox();
	const glm::vec2 mP = ourRect.GetMidpoint();
	const glm::vec2 rP = mP + glm::vec2(ourRect.dim.x / 2.0f, 0);//right point
	glm::vec2 p1 = otherRect.pos; //bottom left point
	glm::vec2 p2 = otherRect.pos + glm::vec2(0, otherRect.dim.y); //top left point
	//extend the collission platform to account for the sprite's height (minus a little not to overlap top/bottom collission)
	p1.y -= ((ourRect.dim.y / 2.0f) - 5.0f);
	p2.y += ((ourRect.dim.y / 2.0f) - 5.0f);

	float hitInfo1, hitInfo2;
	const bool linesIntersect = CollissionUtils::IntersectLineSegments(mP, rP, p1, p2, hitInfo1, hitInfo2);
	//if lines intersect and hitinfo1 (y intersect point) / hitInfo2 (x intersect point) are between 0 and 1
	if (linesIntersect && hitInfo1 > 0 && hitInfo1 < 1 && hitInfo2 > 0 && hitInfo2 < 1) {
		glm::vec3 p = sprite->GetPosition(); //get old position
		p.x = otherRect.pos.x - ourRect.dim.x; //set x value to right of platform - our sprite width
		sprite->SetVelocity(sprite->GetVelocity() * glm::vec3(0, 1, 1));//eliminate x velocity when hitting the wall
		sprite->SetPosition(p);//set new position to sprite
		sprite->OnHit(other, Sprite::HitDirection::RIGHT);
		return true;
	}
	return false;
}
void PhysicsEngine::SetManagedSprites(std::vector<Sprite*>& sprites) { m_rSprites = sprites; }