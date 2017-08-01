#include "Vec2.h"

Vec2 normalizeVec(Vec2 i)
{
	if (i == VEC_NULL) {
		return i;
	}
	Vec2 newVec;
	float length = lengthVec(i);
	newVec.x = i.x / length;
	newVec.y = i.y / length;

	return newVec;
}

float lengthVec(Vec2 v)
{
	return sqrtf(pow(v.x, 2.f) + pow(v.y, 2.f));
}

Vec2 setLengthVec(Vec2 v, float length)
{
	return normalizeVec(v) * length;
}

float getDistanceVec(Vec2 a, Vec2 b)
{
	return sqrt(pow(abs(a.x - b.x),2.f) + pow(abs(a.y - b.y),2.f));
}
