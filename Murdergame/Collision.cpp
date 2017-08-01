#include "Collision.h"

bool isColliding(Vec2 positionA, float radiusA, Vec2 positionB, float radiusB)
{
	float distance = getDistanceVec(positionA, positionB);
	return (distance - radiusA - radiusB) < 0.f;
}
