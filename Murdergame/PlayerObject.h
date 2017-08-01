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
	void updatePosition();
private:
	Vec2 getDirection();
	void handleInput();
};

