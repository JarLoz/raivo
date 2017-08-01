#pragma once
// Some vector related functions.
#include <SFML\System.hpp>
typedef sf::Vector2f Vec2;
// Constants for direction vectors.
const Vec2 VEC_RIGHT(1.f, 0.f);
const Vec2 VEC_UP(0.f, 1.f);
const Vec2 VEC_LEFT(-1.f, 0.f);
const Vec2 VEC_DOWN(0.f, -1.f);
const Vec2 VEC_NULL(0.f, 0.f);

// Normalizes a vector, that is, makes it into a unit vector.
Vec2 normalizeVec(Vec2 v);
// Length of a vector
float lengthVec(Vec2 v);
// Set the vector into a certain lenghth
Vec2 setLengthVec(Vec2 v, float length);
// Get the distance between two points.
float getDistanceVec(Vec2 a, Vec2 b);