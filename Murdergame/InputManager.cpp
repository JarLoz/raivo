#include "InputManager.h"



InputManager * InputManager::getInstance()
{
	if (manager == NULL) {
		manager = new InputManager();
	}
	return manager;
}

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

Vec2 InputManager::getDirection()
{
	// Get keyboard input, set direction.
	Vec2 newDirection = VEC_NULL;
	if (sf::Keyboard::isKeyPressed(MOVE_RIGHT)) {
		newDirection += VEC_RIGHT;
	}
	if (sf::Keyboard::isKeyPressed(MOVE_LEFT)) {
		newDirection += VEC_LEFT;
	}
	if (sf::Keyboard::isKeyPressed(MOVE_UP)) {
		newDirection += VEC_UP;
	}
	if (sf::Keyboard::isKeyPressed(MOVE_DOWN)) {
		newDirection += VEC_DOWN;
	}
	return normalizeVec(newDirection);
}

Vec2 InputManager::getMousePosition(const sf::Window & relativeTo)
{
	Vec2 mousePositionInPixels(sf::Mouse::getPosition(relativeTo));

	mousePositionInPixels.x -= RESOLUTION_X / 2;
	mousePositionInPixels.y = RESOLUTION_Y / 2 - mousePositionInPixels.y;
	Vec2 gamePosition = (mousePositionInPixels / SCALE_FACTOR) + cameraPosition;

	return gamePosition;
}

/*
bool InputManager::getMouseClickLeft()
{
	bool currentState = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (currentState && !mousePressedLeft) {
		mousePressedLeft = true;
		return true;
	} else {
		mousePressedLeft = currentState;
		return false;
	}
}

bool InputManager::getMouseClickRight()
{
	bool currentState = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	if (currentState && !mousePressedRight) {
		mousePressedRight = true;
		return true;
	} else {
		mousePressedRight = currentState;
		return false;
	}
}
*/
