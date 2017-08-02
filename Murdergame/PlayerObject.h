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

	// Implementing sf::Drawable
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
	Vec2 attackDirection;
	Vec2 getDirection();
	void handleInput();
};

