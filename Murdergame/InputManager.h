#pragma once
#include "Main.h"
#include "Globals.h"
class InputManager
{
	Vec2 movementDirection;
	Vec2 mousePosition;
	bool mouseClickLeft;
	bool mouseClickRight;
	bool mousePressedLeft;
	bool mousePressedRight;
public:
	static InputManager* manager;
	static InputManager* getInstance();
	InputManager();
	~InputManager();
	void updateInputs(const sf::Window & relativeTo);
	Vec2 getDirection();
	Vec2 getMousePosition();
	bool getMouseClickLeft();
	bool getMouseClickRight();
	bool getAttack();
	bool closeGame(sf::Window & window);
private:
};

