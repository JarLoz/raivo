#pragma once
#include "Main.h"
#include "GameObject.h"

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
	Vec2 getAttackPosition();
	Vec2 getRelativeMouseDirection() const;
	void handleInput();
};

