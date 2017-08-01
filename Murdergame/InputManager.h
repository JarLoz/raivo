#pragma once
#include "Main.h"
#include "Globals.h"
class InputManager
{
public:
	static InputManager* manager;
	static bool mousePressedLeft;
	static bool mousePressedRight;
	static InputManager* getInstance();
	InputManager();
	~InputManager();
	static Vec2 getDirection();
	static Vec2 getMousePosition(const sf::Window &relativeTo);
	/*
	static bool getMouseClickLeft();
	static bool getMouseClickRight();
	*/
};

