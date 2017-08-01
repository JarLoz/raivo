#pragma once
#include "Main.h"
#include "Globals.h"
class InputManager
{
	bool mousePressedLeft;
	bool mousePressedRight;
public:
	static InputManager* manager;
	static InputManager* getInstance();
	InputManager();
	~InputManager();
	Vec2 getDirection();
	Vec2 getMousePosition(const sf::Window &relativeTo);
	bool getMouseClickLeft();
	bool getMouseClickRight();
	bool closeGame(sf::Window & window);
};

