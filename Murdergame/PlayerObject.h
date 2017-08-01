#pragma once
class PlayerObject;
#include "GameObject.h"
#include "Globals.h"
#include "Collision.h"

class PlayerObject :
	public GameObject
{
public:
	PlayerObject();
	~PlayerObject();
	void update();
private:
	Vec2 getDirection();
};

